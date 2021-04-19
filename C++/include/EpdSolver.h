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
    CellLoop *cellLoop;
    TriSolver *solverEq;
  
  public:

    EpdSolver(Mesh *mesh, Temporal *temporal,
              CellLoop *cellLoop, TriSolver *solver) {
      this->mesh = mesh;
      this->temporal = temporal;      
      this->cellLoop = cellLoop;
      this->solverEq = solver;
    }

    void init(void);

    void solver(Files &files);

};
