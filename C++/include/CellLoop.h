#pragma once

#include"Mesh.h"
#include"Solver.h"
#include"Temporal.h"

class CellLoop {

  public:

    virtual void montaSistema()=0;

};

class CellHeatLoop{

public:

  void montaSistema(TriSolver *solver, Mesh *mesh, Temporal *temporal);

};
