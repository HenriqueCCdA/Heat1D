#ifndef CCCI_H
#define CCCI_H

/*******************************************************************************
 * @brief enumeração que define o tipos de condição de contorno
 *******************************************************************************/
enum typeCc { temp = 1, /**< Tipo de temperatura pescrita. */  
              flux = 2, /**< Tipo de fluxo pescrito. */  
             hConv = 3  /**< Tipo de convecção */
            };

/*******************************************************************************
 *@class CcCi  
 *******************************************************************************
 *@brief     A Classe com as condições de contorno e inicias.
 *@details   A Classe com as condições de contorno e inicias.
 *******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 *******************************************************************************/
class CcCi {

  private:
    int cceType;       /**< Tipo de condição de contorno a esquerda*/
    double cceValue[2];/**< Valores de condição de contorno a esquerda*/
    
    int ccdType;       /**< Tipo de condição de contorno a direita*/
    double ccdValue[2];/**< Valores da condição de contorno a esquerda*/

    double cciValue;  /**< Valor de condição inicial*/

  public:

    // ... setters
    void set_cceType(int value) { this->cceType = value; }

    void set_cceValue(double* value, int n) {
      for(int i = 0; i < n; i++)
        this->cceValue[i] = value[i]; 
    }

    void set_ccdType(int value) { this->ccdType = value; }

    void set_ccdValue(double* value, int n) {
      for (int i = 0; i < n; i++)
        this->ccdValue[i] = value[i];
    }

    void set_cciValue(double value) { this->cciValue = value; }
    // ..........................................................................
    
    // ... getters
    /**************************************************************************
    * @brief Obtém tipo de condição de contorno a esquerda
    **************************************************************************
    * @return retorna o valor do tipo
    **************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    int get_cceType(void) { return this->cceType; }

    /**************************************************************************
    * @brief Obtém os valores da condição de contorno a esquerda
    **************************************************************************
    * @return retorna um ponteiro 
    **************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    double* get_cceValue(void) { return this->cceValue; }

    /**************************************************************************
    * @brief Obtém o valor da condição de contorno a esquerda na posição i
    **************************************************************************
    * @param i - inicie do array
    * @return retorna o valor 
    **************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    double get_cceValue(int i) { return this->cceValue[i]; }

    /**************************************************************************
    * @brief Obtém tipo de condição de contorno a direita
    **************************************************************************
    * @return retorna o valor do tipo
    **************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    int get_ccdType(void) { return this->ccdType; }

    /**************************************************************************
    * @brief Obtém os valores da condição de contorno a esquerda
    **************************************************************************
    * @return retorna um ponteiro
    **************************************************************************
    * @date      19/04/2021 - 25/04/2021
    * @author    Henrique C. C. de Andrade
    ***************************************************************************/
    double* get_ccdValue(void) { return this->ccdValue; }
    
    /**************************************************************************
     * @brief Obtém o valor da condição de contorno a direita na posição i
     **************************************************************************
     * @param i - inicie do array
     * @return retorna o valor
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    double get_ccdValue(int i) { return this->ccdValue[i]; }

    /**************************************************************************
     * @brief Obtém o valor da condição inicial
     **************************************************************************
     * @return retorna o valor
     **************************************************************************
     * @date      19/04/2021 - 25/04/2021
     * @author    Henrique C. C. de Andrade
     ***************************************************************************/
    double get_cciValue(void) { return this->cciValue; }
    // ..........................................................................
};
#endif