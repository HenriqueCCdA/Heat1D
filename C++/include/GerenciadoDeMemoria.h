#pragma once

#include<iostream>

class Memoria {

  public:

    template<typename T> T* alloc(size_t n) {
       T *p = nullptr;       
       
       p = new (std::nothrow) T[n];
       if (!p) {
          std::cout << "Arranjo nao pode ser alocado" << std::endl;
          exit(-1);
       }
       return p;       
    }

    template<typename T>  void dealloc(T **x) {
      delete[] *x;
      *x = nullptr;
    }

};


extern Memoria mem;