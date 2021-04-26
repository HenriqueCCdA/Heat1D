#include"../include/TriaSolver.h"

/******************************************************************************
 *@brief     Allocação da memoria utilizada no solver Tridiagonal.     
 *@details   Allocação da memoria utilizada no solver Tridiagonal. <!--     
 *--> São alocados os arranjos axiliares bm e um.
 ******************************************************************************         
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
void TriSolver::alloc(void) {

  int n = this->get_nEq();

  this->bm = mem.alloc<double>(n);
  this->um = mem.alloc<double>(n);

}
//*****************************************************************************

/******************************************************************************
 *@details   Allocação da memoria utilizada no solver Tridiagonal. <!--
 *-->        São alocados os arranjos axiliares bm e um.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void TriaDiagonal::alloc(void) {

  int n = this->get_n();

  this->b = mem.alloc<double>(n);
  this->l = mem.alloc<double>(n);
  this->d = mem.alloc<double>(n);
  this->u = mem.alloc<double>(n);

}
//*******************************************************************************

/********************************************************************************
 *@brief     Resolução de sistemas de equação tridiagonal.
 *@details   Resolução de sistemas de equação tridiagonal.                                              
 *********************************************************************************
 *@date      2021-2021
 *@author    Henrique C. C. de Andrade
 ********************************************************************************
 * @note
 * Sistema de equações:    
 * <pre>
 *          A        * X  = b                                             
 * | d1 u1  0  0  0 | |x1| |b1|                                           
 * | l2 d2 u2  0  0 | |x2| |b2|                                           
 * | 0  l3 d3 u3  0 |*|x3|=|b3|                                           
 * | 0   0 l4 d4 u4 | |x4| |b4|                                           
 * | 0   0  0 l5 d5 | |x5| |b5|                                           
 * </pre>                                                                       
 *  Estrutura de dados:
 *  <pre>
 *  l = [  0 l2 l3 l4 l5]                                                 
 *  d = [ d1 d2 d3 d4 d5]                                                 
 *  u = [ u1 u2 u3 u4  0]                                                 
 *  </pre>                                                                       
 * fonte: https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm           
 ********************************************************************************/
double* TriSolver::tdma(double *x) {
  int nEq = this->get_nEq();
  TriaDiagonal *triaDiagonal = (TriaDiagonal*) this->get_dataStruct();
  double *u  = triaDiagonal->get_u(),
         *d  = triaDiagonal->get_d(),
         *l  = triaDiagonal->get_l(),
          *b = triaDiagonal->get_b();
  double *um = this->um,
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