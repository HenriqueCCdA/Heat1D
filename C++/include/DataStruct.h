#ifndef DATASTRUCT_H
#define DATASTRUCT_H

class DataStruct {

private:
  int n;

public:
  virtual void alloc(void) = 0;

  // ... setters
  void set_n(int n) { this->n = n; }
  // ..........................................................................

  // ... getters
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

  double* get_l(void) { return this->l; }

  double* get_d(void) { return this->d; }

  double* get_u(void) { return this->u; }

  double* get_b(void) { return this->b; }
  // ..........................................................................

  ~TriaDiagonal() {
    mem.dealloc<double>(&this->b);
    mem.dealloc<double>(&this->l);
    mem.dealloc<double>(&this->d);
    mem.dealloc<double>(&this->u);
  }

};
#endif
