#pragma once

class CcCi {

  private:
    int cceType;
    double cceValue;
    
    int ccdType;
    double ccdValue;

    double cciValue;

  public:

    // setters
    void set_cceType(int value) {
      this->cceType = value;
    }

    void set_cceValue(double value) {
      this->cceValue = value;
    }

    void set_ccdType(int value) {
      this->ccdType = value;
    }

    void set_ccdValue(double value) {
      this->ccdValue = value;
    }

    void set_cciValue(double value) {
      this->cciValue = value;
    }

    // getters
    int get_cceType(void) {
      return this->cceType;
    }

    double get_cceValue(void) {
      return this->cceValue;
    }

    int get_ccdType(void) {
      return this->ccdType;
    }

    double get_ccdValue(void) {
      return this->ccdValue;
    }

    double get_cciValue(void) {
      return this->cciValue;
    }

};