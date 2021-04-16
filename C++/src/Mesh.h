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

    PropRef& getPropRef(void) {
      return this->propRef;
    }

    Cell& getCells(void) {
      return this->cells;
    }

    Node& getNodes(void) {
      return this->nodes;
    }

    CcCi& getCcci(void) {
      return this->ccci;
    }

    int get_nCells(void) {
      return this->getCells().get_nCells();
    }

    int get_nNodes(void) {
      return this->getNodes().get_nNodes();
    }

    double get_l(void) {
      return this->l;
    }   

    void set_l(double d) {
      this->l = d;
    }

    void display(void) {
  
      cout << "**********************************************" << endl;
      cout << "Data:" << endl;

      cout << "length   " << this->get_l() << endl;
      cout << "ndiv     " << this->cells.get_nCells() << endl;
      cout << "dt       " << this->temporal.get_dt() << endl;
      cout << "nstep    " << this->temporal.get_nStep() << endl;
      cout << "ccd      " << this->ccci.get_cceType()  << " "
                          << this->ccci.get_cceValue() << endl;
      cout << "ccd      " << this->ccci.get_ccdType()  << " "
                          << this->ccci.get_ccdValue() << endl;
      cout << "initialt " << this->ccci.get_cciValue() << endl;
      cout << "prop     " << this->propRef.get_rho() << " "
                          << this->propRef.get_cp()  << " "
                          << this->propRef.get_k() << endl;
      cout << "**********************************************" << endl;
    }

    void alloc() {
      
      // alocando os arranjos nodais
      this->nodes.alloc(this->nodes.get_nNodes());
      
      // alocando os arranjos cell
      this->cells.alloc(this->cells.get_nCells());

    }

    void grid(void) {

      int nCells = this->cells.get_nCells();
      int nNodes = this->nodes.get_nNodes();

      double *x = this->nodes.getPx();
      double dx = this->l/nCells;

      this->getCells().set_dx(dx);

      // ...
      x[0] = 0.e0;
      for(int i = 1;i < nNodes - 1;i++)
        x[i] = x[i-1] + dx;
      x[nNodes-1] = this->l;
      // ........................................................................


      // ...
      double *xc = this->cells.getPxc();
      int    *nodes = this->cells.getPnodes();
      for (int i = 0; i < nCells; i++){
          nodes[2*i] = i;
          nodes[2*i + 1] = i + 1;
          xc[i] = (x[ i + 1] + x[i])*0.5e0;
      }
      // ........................................................................

    }

    void plot_coords(void) {
      int nNodes = this->nodes.get_nNodes();
      double *x = this->nodes.getPx();

      for (int i = 0; i < nNodes; i++)
        cout << "x[" << i <<"]" << " = " << x[i] << endl;

    }

    void plot_cells(void) {
      int nCells = this->get_nCells();
      double *xc = this->cells.getPxc();
      int    *nodes = this->cells.getPnodes();

      for (int i = 0; i < nCells; i++)
        cout << "nel = " << i << " (" 
                              << nodes[2 * i] 
                              << ","
                              << nodes[2 * i + 1] 
                              << ") xc = " << xc[i]
                              << endl;

    }


    void nodalInterpol(void) {
      int nCells = this->get_nCells();
      int nNodes = this->get_nNodes();
      int *cells = this->getCells().getPnodes();
      double *nodeU = this->getNodes().getPu();
      double *cellU = this->getCells().getPu();      
      
      // ...
      for (int i = 0; i < nNodes; i++)
        nodeU[i] = 0.e0;
      // ......................................................................

      // ...
      int no1, no2;
      for (int i = 0; i < nCells; i++) {
        no1 = cells[2 * i];
        no2 = cells[2 * i + 1];
        nodeU[no1] += cellU[i];
        nodeU[no2] += cellU[i];
      }
      // ......................................................................

      // ...
      for (int i = 1; i < nNodes - 1; i++)
        nodeU[i] *= 0.5e0;
      // ......................................................................

      // ...
      if(this->ccci.get_cceType() == 1)  
        nodeU[0] = this->ccci.get_cceValue();
      if(this->ccci.get_ccdType() == 1)  
        nodeU[nNodes-1] = this->ccci.get_ccdValue();
      // ......................................................................
    }

    void resNode(ofstream &file, Temporal &temporal) {

      writeResLine(file, temporal.get_iStep(), temporal.get_t(),
                   this->getNodes().getPu(), this->get_nNodes());

    }

    void writeGeomNode(ofstream &file) {

      writeResLine(file, 0, 0.0, this->getNodes().getPx(), this->get_nNodes());

    }

    void resCell(ofstream &file, Temporal &temporal) {

      writeResLine(file, temporal.get_iStep(), temporal.get_t(),
        this->getCells().getPu(), this->get_nCells());

    }

    void writeGeomCell(ofstream &file) {

      writeResLine(file, 0, 0.0, this->getCells().getPxc(), this->get_nCells());

    }



};