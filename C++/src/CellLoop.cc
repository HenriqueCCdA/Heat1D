#include"CellLoop.h"

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
 * u, d, l -> matriz tridiagonal atualizada                           *
 * b -> vetor de forcas atualizado                                    *
 * -------------------------------------------------------------------*
 *********************************************************************/
void CellHeatLoop::montaSistema(TriSolver *solver, Mesh *mesh, 
                                Temporal *temporal) {
  // ...
  double aP0, sU, sP, kf, aE, aW;
  // ..
  double *rho = mesh->getCells().getProp().get_rho();
  double *cp = mesh->getCells().getProp().get_cp();
  double *k = mesh->getCells().getProp().get_k();
  // ...
  double dt = temporal->get_dt();
  double dx = mesh->getCells().get_dx();
  // ...
  int cceType = mesh->getCcci().get_cceType(),
    ccdType = mesh->getCcci().get_ccdType();
  double cceValue = mesh->getCcci().get_cceValue(),
    ccdValue = mesh->getCcci().get_ccdValue();
  double *u = mesh->getCells().getPu();
  // ... sistema de equacoes
  double *aU = solver->get_u(),
    *aD = solver->get_d(),
    *aL = solver->get_l(),
    *b = solver->get_b();
  // ...
  int nCells = mesh->get_nCells(), n;
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