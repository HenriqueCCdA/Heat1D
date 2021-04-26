#ifndef GMEM_H
#define GMEM_H

#include<iostream>
#include"Error.h"

/*******************************************************************************
 *@class Memoria
 *******************************************************************************
 *@brief     A Classe que gerencia a alocação de mémoria.
 *@details   A Classe que gerencia a alocação de mémoria.
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class Memoria {

  public:

    /**************************************************************************
    *@brief Aloca um arranjo                                                   
    *@details Aloca um arranjo de tamanho n. Este metodo utiliza new para      <--
    *-->      a alocação da mémoria
    ***************************************************************************
    * @param numero de termos solicitados                                     
    * @return retorna um ponteiro alocado no heap
    ***************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/

    template<typename T> T* alloc(size_t n) {
       T *p = nullptr;       
       
       if (n<=0) {
         std::cout << "Mem: Numero nulo ou negativo de posicoes !!"<< std::endl;
         exit(error::dimArraySize);
       }

       p = new (std::nothrow) T[n];

       if (!p) {
          std::cout << "Mem: Arranjo nao pode ser alocado" << std::endl;
          exit(error::memory);
       }
       return p;       
    }


    /**************************************************************************
    *@brief Desaloca um arranjo
    *@details Desaloca um arranjo alocado pelo método new.
    ***************************************************************************
    * @param x - Endereção do ponteiro alocado
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