#pragma once
#include"HccaTimeCc.h"

class RunTimes: TimeCc {

  private:
    double sist;
    double solver;
    double res;

  public:

    RunTimes() {
      this->sist = 0.e0;
      this->solver = 0.e0;
      this->res = 0.e0;
    }

    // .. getters
    double getSist(void) { return this->sist; }
    double getSolver(void) { return this->solver; }
    double getRes(void) { return this->res; }
    // ..........................................................................

    // ... metodos
    void init_timer(void) { TimeCc::tic(); }
  
    double toc(void) { return TimeCc::toc(); }

    void updateResTimer(void) { this->res += toc(); }

    void updateSolverTimer(void) { this->solver += toc(); }

    void updateSistTimer(void) { this->sist += toc(); }
    // ..........................................................................

    
};

extern RunTimes times;