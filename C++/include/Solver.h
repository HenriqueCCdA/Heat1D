#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>

#include"GerenciadoDeMemoria.h"
#include"DataStruct.h"

using namespace std;

/*******************************************************************************
 *@class Solver                                                                 
 *******************************************************************************
 *@brief     A Classe que resolve um sistema de equações generico               
 *@details   A Classe que resolve um sistema de equações generico. Esta    <!--      
 *-->  classe tem como principal papel ser herdada.                        
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021                                                          
 *@author    Henrique C. C. de Andrade                                          
 *******************************************************************************/

class Solver {


  private:
    DataStruct *data; /**< Estrutura de dados do sistema de equações*/

  public:
    // ... getters    

    /**************************************************************************
     * @brief Obtem o número de equações do sistema de equações
     **************************************************************************
     * @return retorna a número de equações
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    int get_nEq(void)   { return this->get_dataStruct()->get_n(); }
    
    /***************************************************************************
     * @brief Obtem a estrura de dados utilizado
     ***************************************************************************
     * @return  retorna um ponteiro para a estrutura de dados
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    DataStruct* get_dataStruct(void){return this->data;}

    // ... setters 

    /***************************************************************************
     * @brief Set a estrutura de dados
     ***************************************************************************
     * @param data - Ponteiro para uma estrutura de dados
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    void set_dataStruct(DataStruct* data) { this->data = data; }

    /***************************************************************************
     * @brief Solução do sistema de equações
     ***************************************************************************
     * @param x - solução inicial do solver
     ***************************************************************************
     * @return  retorna a solução do sistema de equações
     ***************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    virtual double* solver(double *x)=0;
};
#endif
