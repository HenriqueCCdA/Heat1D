#ifndef NODE_H
#define NODE_H

#include"../include/GerenciadoDeMemoria.h"

#include<iostream>
using namespace std;

class Node{

  private:
    int nNodes;
    double *x;
    double *u; 

  public:
    // ... setters
    void set_nNodes(int d) { this->nNodes = d; }

    void set_u(double d, int n) {
      for (int i = 0; i < n; i++){
        this->u[i] = d;
      }
    }
    // ..........................................................................

    // ... getters
    int get_nNodes(void) { return this->nNodes; }

    double* getPx() { return this->x; }

    double* getPu() { return this->u; }
    // ..........................................................................
    
    // ... metodos
    void alloc(int n) {
      this->x = mem.alloc<double>(n);
      this->u = mem.alloc<double>(n);
    }
    // ..........................................................................


    // ...
    ~Node() {
      mem.dealloc<double>(&this->x);
      mem.dealloc<double>(&this->u);
    }
    // ..........................................................................

};
#endif