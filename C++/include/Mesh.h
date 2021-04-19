#pragma once

#include<fstream>
#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>

#include "Node.h"
#include "Cell.h"
#include "CcCi.h"
#include "Prop.h"
#include "Temporal.h"

using namespace std;

class Mesh{
  
  private:
    double l;
    Node nodes;
    Cell cells;  
    CcCi  ccci;    
    Temporal temporal;
    PropRef propRef;
    
    static void writeResLine(ofstream &file, int c1, double c2, double *cs, int nCs) {
      file << setw(8) << c1 << " "
           << fixed << setw(12) << setprecision(4) << c2;

      for (int i = 0; i < nCs; i++) {
        file << " " << setprecision(7) << scientific << cs[i];
      }
      file << endl;
    }
  public:

    Mesh(){}

    // ... getters
    PropRef& getPropRef(void) { return this->propRef; }

    Cell& getCells(void) { return this->cells; }

    Node& getNodes(void) { return this->nodes; }

    CcCi& getCcci(void) { return this->ccci; }

    int get_nCells(void) { return this->getCells().get_nCells(); }

    int get_nNodes(void) { return this->getNodes().get_nNodes(); }

    double get_l(void) { return this->l; }   
    // ..........................................................................

    // ... setters
    void set_l(double d) { this->l = d; }
    // ..........................................................................

    // ... metodos
    void display(void); 

    void alloc(); 

    void grid(void);

    void nodalInterpol(void);

    void resNode(ofstream &file, Temporal &temporal); 
    
    void writeGeomNode(ofstream &file); 

    void resCell(ofstream &file, Temporal &temporal);

    void writeGeomCell(ofstream &file); 
    // ..........................................................................
};