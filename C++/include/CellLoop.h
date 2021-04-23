#pragma once

#include"Mesh.h"
#include"Solver.h"
#include"IntTemp.h"


enum cc { cce = 1, ccd = 2 };

class CellLoop {

  public:

    virtual void montaSistema(void)=0;

};

class CellHeatLoop: public CellLoop{

  private:
    Solver *solver;
    Mesh *mesh;
    IntTemp *intTemp; 

  public:

    CellHeatLoop(Solver *solver, Mesh *mesh, IntTemp *intTemp) {
      this->solver = solver;
      this->mesh = mesh;
      this->intTemp = intTemp;
    }

    void montaSistema(void);

};
