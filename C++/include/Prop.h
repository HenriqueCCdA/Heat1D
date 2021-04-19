#pragma once

#include"../include/GerenciadoDeMemoria.h"

class PropRef {

  private:
    double rho;
    double cp;
    double k;

  public:

    // ... setters
    void set_rho(double value) { this->rho = value; }

    void set_cp(double value) { this->cp = value; }

    void set_k(double value) { this->k = value; }

    // ... getters
    double get_rho(void) { return this->rho; }

    double get_cp(void) { return this->cp; }

    double get_k(void) { return this->k; }

};

class Prop {

private:
  double *rho;
  double *cp;
  double *k;

public:

  // ... getters
  double* get_rho(void) { return this->rho; }

  double* get_cp(void) { return this->cp; }

  double* get_k(void) { return this->k; }
  // ..........................................................................


  // ... metodos
  void alloc(int n) {
    this->rho = mem.alloc<double>(n);
    this->cp = mem.alloc<double>(n);
    this->k = mem.alloc<double>(n);    
  }

  void init_prop(PropRef &propRef, int n) {
    for (int i = 0; i < n; i++){
      this->rho[i] = propRef.get_rho();
      this->cp[i]  = propRef.get_cp();
      this->k[i]   = propRef.get_k();
    }
  }
  // ..........................................................................

  // ... Destrutor
  ~Prop() {
    mem.dealloc<double>(&this->rho);
    mem.dealloc<double>(&this->cp);
    mem.dealloc<double>(&this->k);
  }
  // ..........................................................................
};

