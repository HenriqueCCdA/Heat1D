#ifndef GMEM_H
#define GMEM_H

#include<iostream>

/*******************************************************************************
 *@class Memoria
 *******************************************************************************
 *@brief     A Classe que gerencia a aloca��o de m�moria.
 *@details   A Classe que gerencia a aloca��o de m�moria.
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Memoria {

  public:

    /**************************************************************************
    *@brief Aloca um arranjo                                                   
    *@details Aloca um arranjo de tamanho n. Este metodo utiliza new para      <--
    *-->      a aloca��o da m�moria
    ***************************************************************************
    * @param numero de termos solicitados                                     
    * @return retorna um ponteiro alocado no heap
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/

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


    /**************************************************************************
    *@brief Desaloca um arranjo
    *@details Desaloca um arranjo alocado pelo m�todo new.
    ***************************************************************************
    * @param x - Endere��o do ponteiro alocado
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    template<typename T>  void dealloc(T **x) {
      delete[] *x;
      *x = nullptr;
    }

};


extern Memoria mem;

#endif