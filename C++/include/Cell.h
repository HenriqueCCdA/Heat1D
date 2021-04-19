#pragma once

#include"../include/Prop.h"

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
      
      if ((this->xc = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor xc" << endl;
        exit(-1);
      }

      if ((this->u = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor u" << endl;
        exit(-1);
      }

      if ((this->nodes = new int[2*n]) == nullptr) {
        cout << "Erro na alocacao do vetor nodes" << endl;
        exit(-1);
      }


      this->prop.alloc(n);

    }
    // ..........................................................................

    ~Cell() {
      delete[] this->xc;
      delete[] this->u;
      delete[] this->nodes;
    }
};