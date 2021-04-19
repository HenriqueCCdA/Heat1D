#include"../include/EpdSolver.h"
#include"../include/RunTimes.h"

/**********************************************************************
 * Data de Ciacao:       18/04/2021                                   *
 * Data de Modificacao : 00/00/0000                                   *
 * -------------------------------------------------------------------*
 * solver: solução da EDP                                             *
 * ------------------------------------------------------------------ *
 * Parametros de entrada:                                             *
 * ------------------------------------------------------------------ *
 * Files(neq) - aruivos de saida de dados                             *
 * ------------------------------------------------------------------ *
 * Parametros de saida:                                               *
 * ------------------------------------------------------------------ *
 * ------------------------------------------------------------------ *
 * Objetos utilizados:                                                *
 *------------------------------------------------------------------  *
 * TriSolver:                                                         *
 * Mesh:                                                              *
 * temporal:                                                          *
 * ------------------------------------------------------------------ *
 * OBS:                                                               *
 * ------------------------------------------------------------------ *
 *********************************************************************/
void EpdSolver::solver(Files &files){

  int nStep = temporal->get_nStep();
  double *uCell = mesh->getCells().getPu();

  // ...
  times.init_timer();
  mesh->writeGeomNode(files.get_fileOutNode());
  mesh->writeGeomCell(files.get_fileOutCell());
  times.updateResTimer();
  // ............................................................................

  //
  mesh->nodalInterpol();
  // ............................................................................

  // ...
  times.init_timer();
  mesh->resNode(files.get_fileOutNode(), *temporal);
  mesh->resCell(files.get_fileOutCell(), *temporal);
  times.updateResTimer();
  // ............................................................................

  cout << "Running ..." << endl;

  for (int j = 0; j < nStep; j++) {

    // ...
    temporal->updateTime();
    // ..........................................................................

    // ...
    times.init_timer();
    cellLoop->montaSistema(this->solverEq,
                           this->mesh,
                           this->temporal);
    times.updateSistTimer();
    // ..........................................................................

    //... solver
    times.init_timer();
    uCell = solverEq->tdma(uCell);
    times.updateSolverTimer();
    //...........................................................................

    // ... 
    mesh->nodalInterpol();
    //...........................................................................

    // ...
    times.init_timer();
    mesh->resNode(files.get_fileOutNode(), *temporal);
    mesh->resCell(files.get_fileOutCell(), *temporal);
    times.updateResTimer();
    // ..........................................................................   

  }
// ..............................................................................

}
// ******************************************************************************

/********************************************************************************
 * Data de Ciacao:       18/04/2021                                             *
 * Data de Modificacao : 00/00/0000                                             *
 * ---------------------------------------------------------------------------- *
 * solver: solução da EDP                                                       *
 * ---------------------------------------------------------------------------- *
 * Parametros de entrada:                                                       *
 * ---------------------------------------------------------------------------- *
 * Files(neq) - aruivos de saida de dados                                       *
 * ---------------------------------------------------------------------------- *
 * Parametros de saida:                                                         *
 * ---------------------------------------------------------------------------- *
 * ---------------------------------------------------------------------------- *
 * Objetos utilizados:                                                          *
 *----------------------------------------------------------------------------- *
 * TriSolver:                                                                   *
 * Mesh:                                                                        *
 * temporal:                                                                    *
 * ---------------------------------------------------------------------------- *
 * OBS:                                                                         *
 * ---------------------------------------------------------------------------- *
 ********************************************************************************/
void EpdSolver::init(void) {

  int nCells = mesh->getCells().get_nCells();
  double u0 = mesh->getCcci().get_cciValue();
  PropRef propRef = this->mesh->getPropRef();

  // ... iniciando as propriedades
  this->mesh->getCells().getProp().init_prop(propRef, nCells);

  // ... iniciando as celulas
  this->mesh->getCells().set_u(u0, nCells);

  // ... iniciando os nodes
  this->mesh->getNodes().set_u(u0, nCells);

  //
  this->temporal->set_iStep(0);
  this->temporal->set_t(0.0e0);
}
// ******************************************************************************