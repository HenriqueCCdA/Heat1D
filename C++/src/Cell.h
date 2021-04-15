#pragma once

#include"Prop.h"

class Cell {

  private:
    int nCells;
    int *nodes;
    double *u;  
    double *xc;
    Prop prop;        

  public:

    Prop& getProp() {
      return this->prop;
    }

    void set_nCells(int d) {
      this->nCells = d;
    }

    int get_nCells(void) {
      return this->nCells;
    }

    double* getPxc() {
      return this->xc;
    }

    double* getPu() {
      return this->u;
    }

    int* getPnodes() {
      return this->nodes;
    }

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

    void set_u(double d, int n) {
      for (int i = 0; i < n; i++) {
        this->u[i] = d;
      }
    }

    ~Cell() {
      delete[] this->xc;
      delete[] this->u;
      delete[] this->nodes;
    }


};