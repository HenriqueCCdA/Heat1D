#pragma once

#include<iostream>
using namespace std;

class TriSolver {
  private:
    int nEq;
    double *b;
    double *l,*d,*u;
    double *um,*bm;

  public:

    TriSolver(int n) {
      this->nEq = n;
      this->alloc();
    }

    // ... getters
    double* get_l(void) { return  this->l; }

    double* get_d(void) { return this->d; }

    double* get_u(void) { return this->u; }

    double* get_b(void) { return this->b; }
    // ..........................................................................
    
    // ... setters
    void set_nEq(int d) { this->nEq = d; }

    int get_nEq(void) { return this->nEq; }
    // ..........................................................................

    // ...metodos
    void alloc(void);

    double* tdma(double *x);
    // ..........................................................................
    
    // ... detrutor
    ~TriSolver() {
      delete[] this->b;
      delete[] this->l;
      delete[] this->d;
      delete[] this->u;
      delete[] this->um;
      delete[] this->bm;
    }
};
