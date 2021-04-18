#pragma once

class PropRef {

  private:
    double rho;
    double cp;
    double k;

  public:

    // ... setters
    void set_rho(double value) {
      this->rho = value;
    }

    void set_cp(double value) {
      this->cp = value;;
    }

    void set_k(double value) {
      this->k = value;;
    }

    // ... getters
    double get_rho(void) {
      return this->rho;
    }

    double get_cp(void) {
      return this->cp;
    }

    double get_k(void) {
      return this->k;
    }

};

class Prop {

private:
  double *rho;
  double *cp;
  double *k;

public:

  // ... getters
  double* get_rho(void) {
    return this->rho;
  }

  double* get_cp(void) {
    return this->cp;
  }

  double* get_k(void) {
    return this->k;
  }

  void alloc(int n) {
    if ((this->rho = new double[n]) == nullptr) {
      cout << "Erro na alocacao do vetor rho" << endl;
    }

    if ((this->cp = new double[n]) == nullptr) {
      cout << "Erro na alocacao do vetor cp" << endl;
    }

    if ((this->k = new double[n]) == nullptr) {
      cout << "Erro na alocacao do vetor k" << endl;
    }
  }

  void init_prop(PropRef &propRef, int n) {
    for (int i = 0; i < n; i++){
      this->rho[i] = propRef.get_rho();
      this->cp[i]  = propRef.get_cp();
      this->k[i]   = propRef.get_k();
    }
  }
  
  // ... Destrutor
  ~Prop() {
    delete[] this->rho;
    delete[] this->cp;
    delete[] this->k;
  }

};

