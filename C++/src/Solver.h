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

    double* get_l(void) {
      return  this->l;
    }

    double* get_d(void) {
      return this->d;
    }

    double* get_u(void) {
      return this->u;
    }

    double* get_b(void) {
      return this->b;
    }

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

      if ((this->b = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor b" << endl;
        exit(-1);
      }
     
      if ((this->l = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor l" << endl;
        exit(-1);
      }

      if ((this->d = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor d" << endl;
        exit(-1);
      }

      if ((this->u = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor d" << endl;
        exit(-1);
      }

      if ((this->um = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor um" << endl;
        exit(-1);
      }

      if ((this->bm = new double[n]) == nullptr) {
        cout << "Erro na alocacao do vetor bm" << endl;
        exit(-1);
      }

    }

    double* tdma(double *x) {
      int nEq = this->get_nEq();
      double *l = this->l,
             *d = this->d,
             *u = this->u,
             *b = this->b,           
             *um= this->um,
             *bm= this->bm; 

      // ...
      for (int i = 0; i < nEq; i++) {
        um[i] = u[i];
        bm[i] = b[i];
      }
      // ........................................................................

      // ...
      um[0] /= d[0];
      bm[0] /= d[0];
      for (int i = 1; i < nEq - 1; i++) {
        um[i] = um[i] / (d[i] - um[i - 1]*l[i]);
        bm[i] = (bm[i] - bm[i - 1]*l[i]) / (d[i] - um[i - 1]*l[i]);
      }
      int nLast = nEq - 1;
      bm[nLast] = (bm[nLast] - bm[nLast - 1]*l[nLast]) 
                / (d[nLast] - um[nLast - 1]*l[nLast]);
      // ........................................................................

      // ...
      x[nLast] = bm[nLast];
      for (int i = nLast - 1; i > -1; i--) {
        x[i] = bm[i] - um[i] * x[i + 1];
      }
      // ........................................................................

      return x;

    }


    ~TriSolver() {
      delete[] this->b;
      delete[] this->l;
      delete[] this->d;
      delete[] this->u;
      delete[] this->um;
      delete[] this->bm;
    }
};
