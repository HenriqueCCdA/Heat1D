#pragma once

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
      if ((this->x = new double[n]) == nullptr) {
        cout<< "Erro na alocacao do vetor x" << endl;
        exit(-1);
      }

      if ((this->u = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor x" << endl;
        exit(-1);
      }

    }
    // ..........................................................................


    ~Node() {
      delete[] this->x;
      delete[] this->u;
    }

};