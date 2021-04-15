#pragma once

#include"Mesh.h"
#include"Prop.h"
#include"Temporal.h"

class EpdSolver {

  private:
    Mesh *mesh; 
    Temporal *temporal;
  
  public:

    EpdSolver(Mesh *mesh, Temporal *temporal) {
      this->mesh = mesh;
      this->temporal = temporal;      
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
      this->temporal->set_dt(0.e0);
    }
};
