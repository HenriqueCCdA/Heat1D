#ifndef INTTEMP_H
#define INTTEMP_H


/*******************************************************************************
 *@class IntTemp
 *******************************************************************************
 *@brief  Classe com a integração temporal.
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class IntTemp {

  private:    
    int nStep; /**< Número de passos de tempo*/
    int iStep; /**< Passo de tempo*/
    double t;  /**< Tempo total*/
    double dt; /**< Delta T*/

  public:

    /*******************************************************************************
     *@details  Atualiza o passo de tempo e o tempo total.
     *******************************************************************************
     *@date      19/04/2021 - 25/04/2021
     *@author    Henrique C. C. de Andrade
     *******************************************************************************/
    void updateTime() {
      this->t += this->dt;
      this->iStep++;
    }

    //... setters
    void set_nStep(int value){ this->nStep = value; };

    void set_iStep(int value) { this->iStep = value; };

    void set_t(double value){ this->t = value; };

    void set_dt(double value) { this->dt = value; };
    // ..........................................................................

    //... getters
    int get_iStep(void) { return this->iStep; };

    int get_nStep(void) { return this->nStep; };

    double get_dt(void) { return this->dt; };

    double get_t(void) { return this->t; };
    // ..........................................................................

};
#endif