#ifndef TRIASOLVER_H
#define TRIASOLVER_H

#include"Solver.h"

class TriSolver : public Solver {
private:
  double *um, *bm;

public:

  TriSolver() {};

  TriSolver(DataStruct *data) {
    this->set_dataStruct(data);
    this->alloc();
  }

  // ... getters
  int get_nEq(void) { return Solver::get_nEq(); }
  // ..........................................................................

  // ...metodos
  void alloc(void);

  double* solver(double *x) { return this->tdma(x); }

  double* tdma(double *x);
  // ..........................................................................

  // ... detrutor
  ~TriSolver() {
    mem.dealloc<double>(&this->um);
    mem.dealloc<double>(&this->bm);
  }
  // ..........................................................................
};

#endif