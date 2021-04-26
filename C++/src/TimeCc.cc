#include"../include/HccaTimeCc.h"


/*******************************************************************************
 *@details  Inicia o cronometro.
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
void TimeCc::tic() {
  this->t0 = system_clock::now();
}

/*******************************************************************************
 *@details  Finaliza o cronometro.
 *******************************************************************************
 @return Retonar o tempo percorrido desda inicialização do cronometro.
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
double TimeCc::toc() {
  time_point<system_clock> t1 = system_clock::now();
  duration<double> elapsed_seconds = t1 - this->t0;
  return elapsed_seconds.count();
}