#ifndef GMEM_H
#define GMEM_H

#include<iostream>

class Memoria {

  public:

    template<typename T> T* alloc(size_t n) {
       T *p = nullptr;       
       
       if (!n) {
         std::cout << "Mem: Numero nulo de posicoes !!"<< std::endl;
         exit(-1);
       }

       p = new (std::nothrow) T[n];
       if (!p) {
          std::cout << "Mem: Arranjo nao pode ser alocado" << std::endl;
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

#endif