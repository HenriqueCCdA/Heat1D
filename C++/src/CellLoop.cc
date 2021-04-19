#include"../include/CellLoop.h"

/**********************************************************************
 * Data de Ciacao:       18/04/2021                                   *
 * Data de Modificacao : 00/00/0000                                   *
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
 * TriSolver:                                                         *
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
 * temporal                                                           *
 * |_ dt - delta t                                                    *
 * ------------------------------------------------------------------ *
 * OBS:                                                               *
 * ------------------------------------------------------------------ *
 *********************************************************************/
void CellHeatLoop::montaSistema(void){
  // ...
  double aP0, sU, sP, kf, aE, aW;
  // ..
  double *rho = this->mesh->getCells().getProp().get_rho();
  double *cp = this->mesh->getCells().getProp().get_cp();
  double *k = this->mesh->getCells().getProp().get_k();
  // ...
  double dt = this->temporal->get_dt();
  double dx = this->mesh->getCells().get_dx();
  // ...
  int cceType = this->mesh->getCcci().get_cceType(),
    ccdType = this->mesh->getCcci().get_ccdType();
  double cceValue = this->mesh->getCcci().get_cceValue(),
    ccdValue = this->mesh->getCcci().get_ccdValue();
  double *u = this->mesh->getCells().getPu();
  // ... sistema de equacoes
  double *aU = this->solver->get_u(),
    *aD = this->solver->get_d(),
    *aL = this->solver->get_l(),
    *b = this->solver->get_b();
  // ...
  int nCells = this->mesh->get_nCells(), n;
  // ..........................................................................

  // ... temperatura prescrita
  if (cceType == 1) {
    aP0 = rho[0] * cp[0] * dx / dt;
    sU = (2.0e0*k[0] / dx)*cceValue;
    sP = -2.0e0*k[0] / dx;
    kf = (k[0] + k[1])*0.5e0;
    aE = kf / dx;
    // ... W
    aL[0] = 0.0;
    // ... P
    aD[0] = aP0 + aE - sP;
    // ... E
    aU[0] = -aE;
    // c ...
    b[0] = sU + aP0 * u[0];
  }
  // ... fluxo prescrito
  else if (cceType == 2) {

  }
  // ... lei de resfriamento de newton
  else if (cceType == 3) {

  }

  // ... temperatura prescrita
  n = nCells - 1;
  if (ccdType == 1) {
    aP0 = rho[n] * cp[n] * dx / dt;
    sU = (2.0e0*k[n] / dx)*ccdValue;
    sP = -2.0e0*k[n] / dx;
    kf = (k[n - 1] + k[n])*0.5e0;
    aW = kf / dx;
    // ... W
    aL[n] = -aW;
    // ... P
    aD[n] = aP0 + aW - sP;
    // ... E
    aU[n] = 0.0e0;
    // c ...
    b[n] = sU + aP0 * u[n];
  }
  // ... fluxo prescrito
  else if (ccdType == 2) {

  }
  // ... lei de resfriamento de newton
  else if (ccdType == 3) {

  }

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