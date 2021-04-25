#ifndef MESH_H
#define MESH_H

#include<fstream>
#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>

#include"Nodes.h"
#include"Cells.h"
#include"CcCi.h"
#include"Prop.h"
#include"IntTemp.h"

using namespace std;

class Mesh{
  
  private:
    double l;
    Nodes nodes;
    Cells cells;  
    CcCi  ccci;    
    IntTemp *intTemp;
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

    Mesh(IntTemp *intTemp){
      this->intTemp = intTemp;
    }

    // ... getters
    PropRef& get_propRef(void) { return this->propRef; }

    Cells& get_cells(void) { return this->cells; }

    Nodes& get_nodes(void) { return this->nodes; }

    CcCi& get_ccci(void) { return this->ccci; }

    int get_nCells(void) { return this->get_cells().get_nCells(); }

    int get_nNodes(void) { return this->get_nodes().get_nNodes(); }

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

    void resNode(ofstream &file, IntTemp &intTemp); 
    
    void writeGeomNode(ofstream &file); 

    void resCell(ofstream &file, IntTemp &intTemp);

    void writeGeomCell(ofstream &file); 
    // ..........................................................................
};

#endif