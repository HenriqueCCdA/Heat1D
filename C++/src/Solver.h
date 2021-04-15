#pragma once

#include<iostream>
using namespace std;

class TriSolver {
  private:
    int nEq;
    double *b;
    double *x;
    double *l,*d,*u;

  public:

    TriSolver(int n) {
      this->nEq = n;
      this->alloc();
    }

    void set_nEq(int d) {
      this->nEq = d;
    }

    int get_nEq(void) {
      return this->nEq;
    }

    void alloc(void) {
      
      int n = this->nEq;      

      if ((this->b = new double(n)) == nullptr) {
        cout << "Erro na alocacao do vetor b" << endl;
        exit(-1);
      }

      if ((this->x = new double(n)) == nullptr) {
        cout << "Erro na alocacao do vetor x" << endl;
        exit(-1);
      }
      
      if ((this->l = new double(n)) == nullptr) {
        cout << "Erro na alocacao do vetor l" << endl;
        exit(-1);
      }

      if ((this->d = new double(n)) == nullptr) {
        cout << "Erro na alocacao do vetor d" << endl;
        exit(-1);
      }

      if ((this->u = new double(n)) == nullptr) {
        cout << "Erro na alocacao do vetor d" << endl;
        exit(-1);
      }

    }

    ~TriSolver() {
      delete[] this->b;
      delete[] this->x;
      delete[] this->l;
      delete[] this->d;
      delete[] this->u;
    }
};
