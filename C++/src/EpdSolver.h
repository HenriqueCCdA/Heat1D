#pragma once

#include<iostream>

#include"Files.h"
#include"Mesh.h"
#include"Prop.h"
#include"Temporal.h"
#include"CellLoop.h"

using namespace std;

class EpdSolver {

  private:
    Mesh *mesh; 
    Temporal *temporal;
    CellHeatLoop *cellLoop;
    TriSolver *solverEq;
  
  public:

    EpdSolver(Mesh *mesh, Temporal *temporal,
              CellHeatLoop *cellLoop, TriSolver *solver) {
      this->mesh = mesh;
      this->temporal = temporal;      
      this->cellLoop = cellLoop;
      this->solverEq = solver;
    }

    void init(void) {

      int nCells = mesh->getCells().get_nCells();
      double u0 = mesh->getCcci().get_cciValue();
      PropRef propRef = this->mesh->getPropRef();

      // iniciando as propriedades
      this->mesh->getCells().getProp().init_prop(propRef, nCells);

      // iniciando as celulas
      this->mesh->getCells().set_u(u0, nCells);

      //iniciando os nodes
      this->mesh->getNodes().set_u(u0, nCells);

      //
      this->temporal->set_iStep(0);
      this->temporal->set_t(0.0e0);
    }

    void solver(Files &files) {
      int nStep = temporal->get_nStep();

      cout << "Running ..." << endl;

      for(int j = 1; j < nStep; j++) {

        // ...
        temporal->updateTime();
        // ......................................................................

        // ...
        cellLoop->montaSistema( this->solverEq, 
                                this->mesh, 
                                this->temporal);
        // ......................................................................

        // ...
        mesh->resNode(files.get_fileOutNode(), *temporal);
        mesh->resCell(files.get_fileOutCell(), *temporal);
        // .......................................................................

      }
      // .........................................................................

    }
};
