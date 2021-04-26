#ifndef _HCCA_TIMECC_
  #define _HCCA_TIMECC_

  #include<chrono>
  #include<iostream>
  
  using std::chrono::time_point;
  using std::chrono::system_clock;
  using std::chrono::duration;

  /*******************************************************************************
   *@class TimeCc
   *******************************************************************************
   *@brief     Classe para medição do tempo                              
   *******************************************************************************
   *@date      19/04/2021 - 25/04/2021
   *@author    Henrique C. C. de Andrade
   *******************************************************************************/
  class TimeCc {

    private:
      time_point<system_clock> t0; /**< Variavel de tempo utilizada internamente*/
    public:

      /*******************************************************************************
       *@brief     Inicia o cronometro            
      *******************************************************************************/
      void tic();

      /*******************************************************************************
       *@brief     Finaliza o cronometro
       *******************************************************************************/
      double toc();
  };
#endif
