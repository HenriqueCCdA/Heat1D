#pragma once

class Temporal {

  private:    
    int nStep;
    double t, dt;

  public:

    void set_nStep(int value){
      this->nStep = value;
    };

    void set_t(double value){
      this->t = value;
    };

    void set_dt(double value) {
      this->dt = value;
    };

    int get_nStep(void) {
      return this->nStep;
    };

    double get_dt(void) {
      return this->dt;
    };


};
