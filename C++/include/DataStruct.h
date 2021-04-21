#pragma once

class DataStruct {

private:
  int n;

public:
  virtual void alloc(void) = 0;

  // ... setters
  void set_n(int n) { this->n = n; }
  // ..........................................................................

  // ... getters
  virtual double* get_a1(void) = 0;
  virtual double* get_a2(void) = 0;
  virtual double* get_a3(void) = 0;
  virtual double* get_a4(void) = 0;
  virtual double* get_b(void) = 0;
  virtual int get_n(void) { return n; };
  // ..........................................................................


};

class TriaDiagonal : public DataStruct {
private:
  double *b;
  double *l, *d, *u;
public:

  TriaDiagonal(int n) {
    this->set_n(n);
    this->alloc();
  }

  // ...metodos
  void alloc(void);

  // ... setters
  void set_n(int n) { this->DataStruct::set_n(n); }
  // ..........................................................................

  // ... getters
  int get_n(void) { return this->DataStruct::get_n(); }

  double* get_a1(void) { return this->l; }

  double* get_a2(void) { return this->d; }

  double* get_a3(void) { return this->u; }

  double* get_a4(void) { return nullptr; }

  double* get_b(void) { return this->b; }
  // ..........................................................................

  ~TriaDiagonal() {
    mem.dealloc<double>(&this->b);
    mem.dealloc<double>(&this->l);
    mem.dealloc<double>(&this->d);
    mem.dealloc<double>(&this->u);
  }

};
