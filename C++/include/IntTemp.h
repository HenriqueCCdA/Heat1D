#pragma once

class IntTemp {

  private:    
    int nStep, iStep;
    double t, dt;

  public:

    void updateTime() {
      this->t += this->dt;
      this->iStep++;
    }

    //... setters
    void set_nStep(int value){ this->nStep = value; };

    void set_iStep(int value) { this->iStep = value; };

    void set_t(double value){ this->t = value; };

    void set_dt(double value) { this->dt = value; };
    // ..........................................................................

    //... getters
    int get_iStep(void) { return this->iStep; };

    int get_nStep(void) { return this->nStep; };

    double get_dt(void) { return this->dt; };

    double get_t(void) { return this->t; };
    // ..........................................................................

};
