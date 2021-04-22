#pragma once

#include<iostream>

#include"Files.h"
#include"Mesh.h"
#include"Prop.h"
#include"IntTemp.h"
#include"CellLoop.h"

using namespace std;

class EpdSolver {

  private:
    Mesh *mesh; 
    IntTemp *intTemp;
    CellLoop *cellLoop;
    Solver *solverEq;
  
  public:

    EpdSolver(Mesh *mesh, IntTemp *intTemp,
              CellLoop *cellLoop, Solver *solver) {
      this->mesh = mesh;
      this->intTemp = intTemp;      
      this->cellLoop = cellLoop;
      this->solverEq = solver;
    }

    void init(void);

    void solver(Files &files);

};
