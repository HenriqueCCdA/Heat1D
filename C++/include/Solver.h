#pragma once

#include"../include/GerenciadoDeMemoria.h"

#include<iostream>
using namespace std;

class DataStruct {
  
  private:
    int n;

  public:
    virtual void alloc(void)=0;

    // ... setters
    void set_n(int n) { this->n = n; }
    // ..........................................................................

    // ... getters
    virtual double* get_a1(void)=0;
    virtual double* get_a2(void)=0;
    virtual double* get_a3(void)=0;
    virtual double* get_a4(void)=0;
    virtual double* get_b(void)=0;
    virtual int get_n(void){ return n;};
    // ..........................................................................


};

class TriaDiagonal : public DataStruct {
  private:
    double *b;
    double *l, *d, *u;
  public:

    TriaDiagonal(int n) {
      this->set_n(n);
      this->alloc();
    }

  // ...metodos
    void alloc(void);

  // ... setters
    void set_n(int n) { this->DataStruct::set_n(n);}
  // ..........................................................................
  
  // ... getters
    int get_n(void) { return this->DataStruct::get_n();}

    double* get_a1(void) { return this->l; }

    double* get_a2(void) { return this->d; }

    double* get_a3(void) { return this->u; }

    double* get_a4(void) { return nullptr; }

    double* get_b(void) { return this->b; }
  // ..........................................................................

    ~TriaDiagonal() {
      mem.dealloc<double>(&this->b);
      mem.dealloc<double>(&this->l);
      mem.dealloc<double>(&this->d);
      mem.dealloc<double>(&this->u);
    }

};


class Solver {
  private:
    DataStruct *data;

  public:
        
    int get_nEq(void)   { return this->get_dataStruct()->get_n(); }
    
    DataStruct* get_dataStruct(void){return this->data;}

    void set_dataStruct(DataStruct* data) { this->data = data; }

    double* solver(double *x){return x;};
};

class TriSolver: public Solver{
  private:
    double *um,*bm;

  public:

    TriSolver(){};

    TriSolver(DataStruct *data) {
      this->set_dataStruct(data);
      this->alloc();
    }
     
    // ... getters
    int get_nEq(void) { return Solver::get_nEq(); }
    // ..........................................................................

    // ...metodos
    void alloc(void);

    double* solver(double *x){ return this->tdma(x);}

    double* tdma(double *x);
    // ..........................................................................
    
    // ... detrutor
    ~TriSolver() {
      mem.dealloc<double>(&this->um);
      mem.dealloc<double>(&this->bm);     
    }
    // ..........................................................................
};
