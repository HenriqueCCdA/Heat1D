#pragma once

#include"../include/Prop.h"
#include"../include/GerenciadoDeMemoria.h"

class Cell {

  private:
    int nCells;
    int *nodes;
    double *u;  
    double *xc;
    double dx;
    Prop prop;        

  public:

    // ... setters
    void set_dx(double d) { this->dx = d; }

    void set_nCells(int d) { this->nCells = d; }

    void set_u(double d, int n) {
      for (int i = 0; i < n; i++) {
        this->u[i] = d;
      }
    }
    // ..........................................................................

    // ... getters
    double get_dx(void) { return this->dx; }

    Prop& getProp() { return this->prop; }

    int get_nCells(void) { return this->nCells; }

    double* getPxc() { return this->xc; }

    double* getPu() { return this->u; }

    int* getPnodes() { return this->nodes; }
    // ..........................................................................

    // ... metodos
    void alloc(int n) {
      
      this->xc = mem.alloc<double>(n);
      this->u = mem.alloc<double>(n);
      this->nodes = mem.alloc<int>(2*n);

      this->prop.alloc(n);

    }
    // ..........................................................................

    ~Cell() {
      mem.dealloc<double>(&this->xc);
      mem.dealloc<double>(&this->u);
      mem.dealloc<int>(&this->nodes);

    }
};