#ifndef CCCI_H
#define CCCI_H

enum typeCc { temp = 1, flux = 2, hConv = 3 };

class CcCi {

  private:
    int cceType;
    double cceValue[2];
    
    int ccdType;
    double ccdValue[2];

    double cciValue;

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
    int get_cceType(void) { return this->cceType; }

    double* get_cceValue(void) { return this->cceValue; }
    double get_cceValue(int i) { return this->cceValue[i]; }

    int get_ccdType(void) { return this->ccdType; }

    double* get_ccdValue(void) { return this->ccdValue; }
    double get_ccdValue(int i) { return this->ccdValue[i]; }

    double get_cciValue(void) { return this->cciValue; }
    // ..........................................................................
};
#endif