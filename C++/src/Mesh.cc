#include"../include/Mesh.h"

/***************************************************************************
 *@brief Mostra informações importantes da malha.
 **************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ***************************************************************************/
void Mesh::display(void) {

  cout << "**********************************************" << endl;
  cout << "Data:" << endl;

  cout << "length   " << this->get_l() << endl;
  cout << "ndiv     " << this->cells.get_nCells() << endl;
  cout << "dt       " << this->intTemp->get_dt() << endl;
  cout << "nstep    " << this->intTemp->get_nStep() << endl;
  cout << "cce      " << this->ccci.get_cceType() << " "
    << this->ccci.get_cceValue(0) << endl;
  cout << "ccd      " << this->ccci.get_ccdType() << " "
    << this->ccci.get_ccdValue(0) << endl;
  cout << "initialt " << this->ccci.get_cciValue() << endl;
  cout << "prop     " << this->propRef.get_rho() << " "
    << this->propRef.get_cp() << " "
    << this->propRef.get_k() << endl;
  cout << "**********************************************" << endl;
}
/**********************************************************************/

/******************************************************************************
 *@details Aloca a memoria necessaria. Este metodo delega a alocação para os   <!--
 *<--      métodos dos ojetos nodes e cells. 
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void Mesh::alloc() {

  // alocando os arranjos nodais
  this->nodes.alloc(this->nodes.get_nNodes());

  // alocando os arranjos Cells
  this->cells.alloc(this->cells.get_nCells());

}
/**********************************************************************/

/******************************************************************************
 *@details Gera o grid. O grid é uniforme.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void Mesh::grid(void) {

  int nCells = this->cells.get_nCells();
  int nNodes = this->nodes.get_nNodes();

  double *x = this->nodes.get_x();
  double dx = this->l / nCells;

  this->get_cells().set_dx(dx);

  // ...
  x[0] = 0.e0;
  for (int i = 1; i < nNodes - 1; i++)
    x[i] = x[i - 1] + dx;
  x[nNodes - 1] = this->l;
  // ........................................................................


  // ...
  double *xc = this->cells.get_xc();
  int    *nodes = this->cells.get_nodes();
  for (int i = 0; i < nCells; i++) {
    nodes[2 * i] = i;
    nodes[2 * i + 1] = i + 1;
    xc[i] = (x[i + 1] + x[i])*0.5e0;
  }
  // ........................................................................

}
/******************************************************************************/

/******************************************************************************
 *@details Interpola valores das céluas para o nós.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void Mesh::nodalInterpol(void) {
  int nCells = this->get_nCells();
  int nNodes = this->get_nNodes();
  int *cells = this->get_cells().get_nodes();
  double *nodeU = this->get_nodes().get_u();
  double *cellU = this->get_cells().get_u();

  // ...
  for (int i = 0; i < nNodes; i++)
    nodeU[i] = 0.e0;
  // ......................................................................

  // ...
  int no1, no2;
  for (int i = 0; i < nCells; i++) {
    no1 = cells[2 * i];
    no2 = cells[2 * i + 1];
    nodeU[no1] += cellU[i];
    nodeU[no2] += cellU[i];
  }
  // ......................................................................

  // ...
  for (int i = 1; i < nNodes - 1; i++)
    nodeU[i] *= 0.5e0;
  // ......................................................................

  // ...
  if (this->ccci.get_cceType() == typeCc::temp)
    nodeU[0] = this->ccci.get_cceValue(0);
  if (this->ccci.get_ccdType() == typeCc::temp)
    nodeU[nNodes - 1] = this->ccci.get_ccdValue(0);
  // ......................................................................
}
/*****************************************************************************/