#pragma once
#include<string>
#include<iostream>
#include<fstream>

#include"Temporal.h"
#include"Mesh.h"


using namespace std;


class Files {

  private:
    string nameIn;
    string nameOut;  
    ofstream fileOutCell;
    ofstream fileOutNode;

  public:

    Files(){}

    // ... setters
    void set_nameOut(string value) { this->nameOut = value; }

    void set_nameIn(string value) { this->nameIn = value; }
    // ..........................................................................

    // ... getters
    ofstream& get_fileOutNode() { return this->fileOutNode; }

    ofstream& get_fileOutCell() { return this->fileOutCell; }

    string get_nameOut(void) { return this->nameOut; }

    string get_nameIn(void) { return this->nameIn; }
    // ..........................................................................

    // ... metodos
    void openOutputFile(void);

    void closeOutputFile(void) {
      fileOutNode.close();
    }

    void read(Mesh &mesh, Temporal &temporal);
    // .......................................................................... 
};
