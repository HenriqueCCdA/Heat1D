#ifndef _HCCA_TIMECC_
  #define _HCCA_TIMECC_

  #include<chrono>
  #include<iostream>
  
  using std::chrono::time_point;
  using std::chrono::system_clock;
  using std::chrono::duration;

  class TimeCc {

    private:
      time_point<system_clock> t0;
    public:
      void tic();
      double toc();
  };
#endif
