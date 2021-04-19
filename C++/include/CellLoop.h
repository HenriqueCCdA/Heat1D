#pragma once

#include"Mesh.h"
#include"Solver.h"
#include"Temporal.h"

class CellLoop {

  public:

    virtual void montaSistema(void)=0;

};

class CellHeatLoop: public CellLoop{

  private:
    TriSolver *solver;
    Mesh *mesh;
    Temporal *temporal; 

  public:

    CellHeatLoop(TriSolver *solver, Mesh *mesh, Temporal *temporal) {
      this->solver = solver;
      this->mesh = mesh;
      this->temporal = temporal;
    }

    void montaSistema(void);

};
