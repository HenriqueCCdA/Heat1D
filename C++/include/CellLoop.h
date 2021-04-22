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
    Solver *solver;
    Mesh *mesh;
    IntTemp *temporal; 

  public:

    CellHeatLoop(Solver *solver, Mesh *mesh, IntTemp *temporal) {
      this->solver = solver;
      this->mesh = mesh;
      this->temporal = temporal;
    }

    void montaSistema(void);

};
