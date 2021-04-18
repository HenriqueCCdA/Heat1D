#include"Solver.h"

/**********************************************************************
 * Data de Ciacao:       18/04/2021                                   *
 * Data de Modificacao : 00/00/0000                                   *
 * -------------------------------------------------------------------*
 * alloc: allocacoa da memoria utilizada no solver Tridiagonal        *
 * ------------------------------------------------------------------ *
 * Parametros de entrada:                                             *
 * ------------------------------------------------------------------ *
 * x(neq)   - vetor independente                                      *
 * ------------------------------------------------------------------ *
 * Parametros de saida:                                               *
 * ------------------------------------------------------------------ *
 * x(neq) - vetor solucao                                             *
 * ------------------------------------------------------------------ *
 * Objetos utilizados:                                                *
 *------------------------------------------------------------------  *
 * TriSolver:                                                         *
 * l[neq]   - diagonal inferior  (alocado)                            *
 * d[neq]   - diagonal principal (alocado)                            *
 * u[neq]   - diagonal superio   (alocado)                            *
 * b[neq]   - vetor independente (alocado)                            *
 *um[neq]   - vetor auxiliar     (alocado)                            *
 *bm[neq]   - vetor auxiliar     (alocado)                            *
 * ------------------------------------------------------------------ *
 * OBS:                                                               *
 * ------------------------------------------------------------------ *
 *********************************************************************/
void TriSolver::alloc(void) {

  int n = this->nEq;

  if ((this->b = new double[n]) == nullptr) {
    cout << "Erro na alocacao do vetor b" << endl;
    exit(-1);
  }

  if ((this->l = new double[n]) == nullptr) {
    cout << "Erro na alocacao do vetor l" << endl;
    exit(-1);
  }

  if ((this->d = new double[n]) == nullptr) {
    cout << "Erro na alocacao do vetor d" << endl;
    exit(-1);
  }

  if ((this->u = new double[n]) == nullptr) {
    cout << "Erro na alocacao do vetor d" << endl;
    exit(-1);
  }

  if ((this->um = new double[n]) == nullptr) {
    cout << "Erro na alocacao do vetor um" << endl;
    exit(-1);
  }

  if ((this->bm = new double[n]) == nullptr) {
    cout << "Erro na alocacao do vetor bm" << endl;
    exit(-1);
  }

}
//*********************************************************************

/**********************************************************************
 * Data de criacao    : 18/04/2021                                    *
 * Data de modificaco : 00/00/0000                                    *
 * ------------------------------------------------------------------ *
 * tdma : resolucao de sistemas tridiagonais                          *
 * ------------------------------------------------------------------ *
 * Parametros de entrada:                                             *
 * ------------------------------------------------------------------ *
 * x(neq)   - vetor independente                                      *
 * ------------------------------------------------------------------ *
 * Parametros de saida:                                               *
 * ------------------------------------------------------------------ *
 * x(neq) - vetor solucao                                             *
 * ------------------------------------------------------------------ *
 * Objetos utilizados:                                                *
 *------------------------------------------------------------------  *
 * TriSolver:                                                         *
 * l[neq]   - diagonal inferior  (inalterado)                         *
 * d[neq]   - diagonal principal (inalterado)                         *
 * u[neq]   - diagonal superio   (inalterado)                         *
 * b[neq]   - vetor independente (inalterado)                         *
 *um[neq]   - vetor auxiliar                                          *
 *bm[neq]   - vetor auxiliar                                          *
 * ------------------------------------------------------------------ *
 * OBS:                                                               *
 * ------------------------------------------------------------------ *
 * | d1 u1  0  0  0 | |x1| |b1|                                       *
 * | l2 d2 u2  0  0 | |x2| |b2|                                       *
 * | 0  l3 d3 u3  0 |*|x3|=|b3|                                       *
 * | 0   0 l4 d4 u4 | |x4| |b4|                                       *
 * | 0   0  0 l5 d5 | |x5| |b5|                                       *
 *                                                                    *
 * l = [  0 l2 l3 l4 l5]                                              *
 * d = [ d1 d2 d3 d4 d5]                                              *
 * u = [ u1 u2 u3 u4  0]                                              *
 *                                                                    *
 * fonte: https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm  *
 *********************************************************************/
double* TriSolver::tdma(double *x) {
  int nEq = this->get_nEq();
  double *l = this->l,
    *d = this->d,
    *u = this->u,
    *b = this->b,
    *um = this->um,
    *bm = this->bm;

  // ...
  for (int i = 0; i < nEq; i++) {
    um[i] = u[i];
    bm[i] = b[i];
  }
  // ........................................................................

  // ...
  um[0] /= d[0];
  bm[0] /= d[0];
  for (int i = 1; i < nEq - 1; i++) {
    um[i] = um[i] / (d[i] - um[i - 1] * l[i]);
    bm[i] = (bm[i] - bm[i - 1] * l[i]) / (d[i] - um[i - 1] * l[i]);
  }
  int nLast = nEq - 1;
  bm[nLast] = (bm[nLast] - bm[nLast - 1] * l[nLast])
    / (d[nLast] - um[nLast - 1] * l[nLast]);
  // ........................................................................

  // ...
  x[nLast] = bm[nLast];
  for (int i = nLast - 1; i > -1; i--) {
    x[i] = bm[i] - um[i] * x[i + 1];
  }
  // ........................................................................

  return x;

}
// ***************************************************************************