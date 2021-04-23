#ifndef SOLVER_H
#define SOLVER_H


#include"../include/GerenciadoDeMemoria.h"
#include"../include/DataStruct.h"

#include<iostream>
using namespace std;


class Solver {
  private:
    DataStruct *data;

  public:
        
    int get_nEq(void)   { return this->get_dataStruct()->get_n(); }
    
    DataStruct* get_dataStruct(void){return this->data;}

    void set_dataStruct(DataStruct* data) { this->data = data; }

    virtual double* solver(double *x)=0;
};
#endif
