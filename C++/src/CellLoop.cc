#include"../include/CellLoop.h"

static void cc(double &aL, double &aD, double &aU, double &b
      , double rho, double cp, double kP, double kV
      , double dx, double dt, double u
      , short ccType, double *aCcValue, short c);


/**********************************************************************
 * Data de Ciacao:       18/04/2021                                   *
 * Data de Modificacao : 22/04/2021                                   *
 * -------------------------------------------------------------------*
 * montaSistema: loop nas celulas para montar os sistema de equacoes  *
 * -------------------------------------------------------------------*
 * Parametros de Entrada:                                             *
 * -------------------------------------------------------------------*
 * -------------------------------------------------------------------*
 * Parametros de Saida:                                               *
 * -------------------------------------------------------------------*
 * ------------------------------------------------------------------ *
 * Objetos utilizados:                                                *
 *------------------------------------------------------------------  *
 * DataStrucr:                                                        *
 *  |_ l[neq] - diagonal inferior  (alterado)                         *
 *  |_ d[neq] - diagonal principal (alterado)                         *
 *  |_ u[neq] - diagonal superio   (alterado)                         *
 *  |_ b[neq] - vetor independente (alterado)                         *
 * Mesh:                                                              *
 * |_ cells:                                                          *
 *    |_ u - valores da solucao por celula                            *
 * |  |_ prop:                                                        *
 * |     |_ rho - massa especifica                                    *
 * |     |_ cp  - calor especifico                                    *
 * |     |_ k   - coeficiente de difusao                              *
 * |_ cccci:                                                          *
 *       |_ cceType  - tipo de condicao de contorno esquerda          *
 *       |_ cceValue - valor de condicao de contorno esquerda         *
 *       |_ ccdType  - tipo de condicao de contorno direita           *
 *       |_ ccdValue - valor de condicao de contorno esquerda         *
 * intTemp                                                           *
 * |_ dt - delta t                                                    *
 * ------------------------------------------------------------------ *
 * OBS:                                                               *
 * ------------------------------------------------------------------ *
 *********************************************************************/
void CellHeatLoop::montaSistema(void){
  // ...
  double aP0, kf, aE, aW;
  // ..
  double *rho = this->mesh->getCells().getProp().get_rho();
  double *cp = this->mesh->getCells().getProp().get_cp();
  double *k = this->mesh->getCells().getProp().get_k();
  // ...
  double dt = this->intTemp->get_dt();
  double dx = this->mesh->getCells().get_dx();
  // ...
  int cceType = this->mesh->getCcci().get_cceType(),
      ccdType = this->mesh->getCcci().get_ccdType();
  double *cceValue = this->mesh->getCcci().get_cceValue(),
         *ccdValue = this->mesh->getCcci().get_ccdValue();
  double *u = this->mesh->getCells().getPu();
  // ... sistema de equacoes
  double *aU = this->solver->get_dataStruct()->get_a3(),
         *aD = this->solver->get_dataStruct()->get_a2(),
         *aL = this->solver->get_dataStruct()->get_a1(),
          *b = this->solver->get_dataStruct()->get_b();
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
 * Data de Ciacao:       22/04/2021                                             *
 * Data de Modificacao : 00/00/0000                                             *
 * ---------------------------------------------------------------------------- *
 * cc: aplicao da condicoes de contorno                                         *
 * ---------------------------------------------------------------------------- *
 * Parametros de entrada:                                                       *
 * ---------------------------------------------------------------------------- *
 * aL      - termo diagonal inverior                                            *
 * aD      - termo diagonal principal                                           *
 * aU      - termo diagonal superio                                             *
 * b       - termo vetor de forcas                                              *
 * rho     - massa especifica                                                   *
 * cp      - calor especifico                                                   *
 * kP      - coeficiente de difusao da celula central                           *
 * kV      - coeficiente de difusao da celula vizina                            *
 * h       - coeficiente de calor convectivo                                    *
 * dx      - tamanho da celula                                                  *
 * dt      - passo de tempo                                                     *
 * u       - valor da solução do passo de tempo anterior                        *
 * ccType  - tipo da condicao de contorno                                       *
 * ccValue - parametros da condicao de contorno                                 *
 * ---------------------------------------------------------------------------- *
 * Parametros de saida:                                                         *
 * ---------------------------------------------------------------------------- *
 * aL      - termo diagonal inverior                                            *
 * aD      - termo diagonal principal                                           *
 * aU      - termo diagonal superio                                             *
 * b       - termo vetor de forcas                                              *
 * ---------------------------------------------------------------------------- *
 * Objetos utilizados:                                                          *
 *----------------------------------------------------------------------------- *
 * ---------------------------------------------------------------------------- *
 * OBS:                                                                         *
 * ---------------------------------------------------------------------------- *
 ********************************************************************************/
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