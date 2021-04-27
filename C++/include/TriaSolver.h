#ifndef TRIASOLVER_H
#define TRIASOLVER_H

#include"Solver.h"

/******************************************************************************
 *@class TriSolver
 ******************************************************************************
 *@brief     A Classe que resolve um sistema de equações tridiagonais
 *@details   A Classe que resolve um sistema de equações tridiagonais. Esta <!--
 * -->  classe é filha da classe solver. Além dos vetores u, l, d e b       <!--
 * -->  do sistema de equacões essas classe precisa dos vetores auxiliares  <!--
 * -->  um e bm. Todos esses vetores tem a dimenssão igual a nEq.
 *******************************************************************************
 * @date      19/04/2021 - 25/04/2021
 * @author    Henrique C. C. de Andrade
 ******************************************************************************
*******************************************************************************/

class TriSolver : public Solver {

  private:
    
    // ...
    double *um; /**< Arranjo auxiliar do solver tridiagonal*/
    double *bm; /**< Arranjo auxiliar do solver tridiagonal*/
    // .......................................................................... 

    // ...
    double* tdma(double *x);
    // ..........................................................................

  public:

    // ... Contrutor
    
    /*************************************************************************** 
     *@brief Contrutor
     *@details Este construtor recebe um ponteiro para dataStruct. Além disso <!--
     * --> esse método aloca os vetores um e bm.
     **************************************************************************          
     *@date      19/04/2021 - 25/04/2021
     *@author    Henrique C. C. de Andrade
    ***************************************************************************/ 
    TriSolver(DataStruct *data) {
      this->set_dataStruct(data);
      this->alloc();
    }
    // ..........................................................................

    // ... getters
    
    /***************************************************************************
     * @brief Obtem o número de equações do sistema de equações
     **************************************************************************
     * @return retorna a número de equações
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/ 
    int get_nEq(void) { return Solver::get_nEq(); }
    // ..........................................................................

    // ...metodos    
    void alloc(void);

    double* solver(double *x) override { return this->tdma(x); }
    // ..........................................................................

    // ... detrutor
    /***************************************************************************
     * @brief Destrutor
     * @details Este destrutor libera a memoria utilizada nos arranjos um e bm.
     **************************************************************************  
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    ~TriSolver() {
      mem.dealloc<double>(&this->um);
      mem.dealloc<double>(&this->bm);
    }
    // ..........................................................................
};

#endif