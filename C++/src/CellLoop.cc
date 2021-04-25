#include"../include/CellLoop.h"

static void cc(double &aL, double &aD, double &aU, double &b
      , double rho, double cp, double kP, double kV
      , double dx, double dt, double u
      , short ccType, double *aCcValue, short c);

/********************************************************************************
 *@brief     Monta o sistema de equações atraves do loop nas celulas.
 *@details   Monta o sistema de equações atraves do loop nas celulas. <!--
 *-->        A estrutura de dados do sistema de equações é atualizado <!--
 *-->        no final do método.
 ********************************************************************************
 *@date      19/04/2021 - 24/04/2021
 *@author    Henrique C. C. de Andrade
 ********************************************************************************/
void CellHeatLoop::montaSistema(void){
  // ...
  double aP0, kf, aE, aW;
  // ..
  double *rho = this->mesh->get_cells().get_prop().get_rho();
  double *cp = this->mesh->get_cells().get_prop().get_cp();
  double *k = this->mesh->get_cells().get_prop().get_k();
  // ...
  double dt = this->intTemp->get_dt();
  double dx = this->mesh->get_cells().get_dx();
  // ...
  int cceType = this->mesh->get_ccci().get_cceType(),
      ccdType = this->mesh->get_ccci().get_ccdType();
  double *cceValue = this->mesh->get_ccci().get_cceValue(),
         *ccdValue = this->mesh->get_ccci().get_ccdValue();
  double *u = this->mesh->get_cells().get_u();
  // ... sistema de equacoes
  TriaDiagonal *triaDiagonal = (TriaDiagonal*) this->solver->get_dataStruct();
  double *aU = triaDiagonal->get_u(),
         *aD = triaDiagonal->get_d(),
         *aL = triaDiagonal->get_l(),
          *b = triaDiagonal->get_b();
  // ...
  int nCells = this->mesh->get_nCells(), n;
  // ..........................................................................

  // ... Lado esquerdo
  cc(aL[0]  , aD[0], aU[0], b[0],
     rho[0] , cp[0], k[0] , k[1],
     dx     , dt   , u[0],  
     cceType, cceValue, cce);
  // ............................................................................


  // ... Lado direito
  n = nCells - 1;
  cc(aL[n] , aD[n]   , aU[n], b[n],
    rho[n] , cp[n]   ,  k[n], k[n-1],
    dx     , dt      , u[n],
    ccdType, ccdValue, ccd);
  // ............................................................................
 
  // ... loop nas celulas do interios
  for (int i = 1; i < nCells - 1; i++) {
    aP0 = rho[i] * cp[i] * dx / dt;
    // ... w
    kf = (k[i - 1] + k[i])*0.5e0;
    aW = kf / dx;
    // ...
    kf = (k[i] + k[i + 1])*0.5e0;
    aE = kf / dx;
    // ...
    aL[i] = -aW;
    aD[i] = aP0 + aW + aE;
    aU[i] = -aE;
    // ...
    b[i] = aP0 * u[i];
  }
  // ..........................................................................
}
//*****************************************************************************

/********************************************************************************
 *@brief     Função auxiliar para aplicar as condições de contorno.
 *@details   Função auxiliar para aplicar as condições de contorno.
 ********************************************************************************
 *@param   aL      - termo diagonal inverior
 *@param   aD      - termo diagonal principal
 *@param   aU      - termo diagonal superio
 *@param   b       - termo vetor de forcas
 *@param   rho     - massa especifica
 *@param   cp      - calor especifico
 *@param   kP      - coeficiente de difusao da celula central
 *@param   kV      - coeficiente de difusao da celula vizina
 *@param   h       - coeficiente de calor convectivo
 *@param   dx      - tamanho da celula
 *@param   dt      - passo de tempo
 *@param   u       - valor da solução do passo de tempo anterior
 *@param   ccType  - tipo da condicao de contorno
 *@param   ccValue - parametros da condicao de contorno      
 ********************************************************************************
 *@date      19/04/2021 - 24/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
static void cc(double &aL, double &aD, double &aU, double &b
             , double rho, double cp, double kP, double kV
             , double dx, double dt, double u
             , short ccType, double *aCcValue, short c) {

  double aP0, sU, sP, kf, aWorE;
  double ccValue = aCcValue[0];

  aP0 = rho * cp * dx / dt;
  kf = (kP + kV)*0.5e0;
  aWorE = kf / dx;
  // ... temperatura prescrita
  if (ccType == typeCc::temp) {
    sU = (2.0e0*kP / dx)*ccValue;
    sP = -2.0e0*kP / dx;
  }
  // ... fluxo prescrito
  else if (ccType == typeCc::flux) {
    sU    = -ccValue;
    sP    = 0.0;
  }
  // ... lei de resfriamento de newton
  else if (ccType == typeCc::hConv) {
    double h = aCcValue[1];
    double tmp = 1.e0 + (h*2.e0*dx)/kP;
    tmp = h/tmp;
    sU = tmp*ccValue;
    sP = -tmp;
  }
  // ............................................................................

  // ... W
  aL = -((c == cce) ? -0.0 : aWorE);
  // ... P
  aD = aP0 + aWorE - sP;
  // ... E
  aU = -((c == ccd) ? -0.0 : aWorE);
  // c ...
  b = sU + aP0 * u;
  // ............................................................................
}
/******************************************************************************/