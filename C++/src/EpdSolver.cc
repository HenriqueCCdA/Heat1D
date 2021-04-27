#include"../include/EpdSolver.h"
#include"../include/RunTimes.h"

/********************************************************************************
*@details Procedimento principal da solução da EDP. Neste método e executado     <!--
*-->      o fluxo principal de solução.
*********************************************************************************
*@param files - arquivos de saida de dados  
*********************************************************************************
*@date      19/04/2021 - 25/04/2021
*@author    Henrique C. C. de Andrade
*******************************************************************************/
void EpdSolver::solver(Files &files){

  int nStep = intTemp->get_nStep();
  double *uCell = mesh->get_cells().get_u();

  // ...
  times.init_timer();
  files.writeGeomNode(*this->mesh);
  files.writeGeomCell(*this->mesh);
  times.updateResTimer();
  // ............................................................................

  //
  mesh->nodalInterpol();
  // ............................................................................

  // ...
  times.init_timer();
  files.resNode(*this->mesh, *intTemp);
  files.resCell(*this->mesh, *intTemp);
  times.updateResTimer();
  // ............................................................................

  cout << "Running ..." << endl;

  for (int j = 0; j < nStep; j++) {

    // ...
    intTemp->updateTime();
    // ..........................................................................

    // ...
    times.init_timer();
    cellLoop->montaSistema();
    times.updateSistTimer();
    // ..........................................................................

    //... solver
    times.init_timer();
    uCell = solverEq->solver(uCell);
    times.updateSolverTimer();
    //...........................................................................

    // ... 
    mesh->nodalInterpol();
    //...........................................................................

    // ...
    times.init_timer();
    files.resNode(*this->mesh, *intTemp);
    files.resCell(*this->mesh, *intTemp);
    times.updateResTimer();
    // ..........................................................................   

  }
// ..............................................................................

}
// ******************************************************************************

 /********************************************************************************
 *@details Inicialação dos dado para procedimento de solução da EDP. Esta função  <!--
 *<--      precisa ser chamada antes de método solver
 *********************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
void EpdSolver::init(void) {

  int nCells = mesh->get_cells().get_nCells();
  double u0 = mesh->get_ccci().get_cciValue();
  PropRef propRef = this->mesh->get_propRef();

  // ... iniciando as propriedades
  this->mesh->get_cells().get_prop().init_prop(propRef, nCells);

  // ... iniciando as celulas
  this->mesh->get_cells().set_u(u0, nCells);

  // ... iniciando os nodes
  this->mesh->get_nodes().set_u(u0, nCells);

  //
  this->intTemp->set_iStep(0);
  this->intTemp->set_t(0.0e0);
}
// ******************************************************************************