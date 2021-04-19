#include"../include/HccaTimeCc.h"

void TimeCc::tic() {
  this->t0 = system_clock::now();
}

double TimeCc::toc() {
  time_point<system_clock> t1 = system_clock::now();
  duration<double> elapsed_seconds = t1 - this->t0;
  return elapsed_seconds.count();
}