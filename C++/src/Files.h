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

    void set_nameOut(string value) {
      this->nameOut = value;
    }

    void set_nameIn(string value) {
      this->nameIn = value;
    }

    ofstream& get_fileOutNode() {
      return this->fileOutNode;
    }

    ofstream& get_fileOutCell() {
      return this->fileOutCell;
    }

    string get_nameOut(void) {
      return this->nameOut;
    }

    string get_nameIn(void) {
      return this->nameIn;
    }

    void openOutputFile(void) {
      string name = this->nameOut + "_node.c++";

      fileOutNode.open(name, ios::out);
      if (!fileOutNode.is_open()) {
        cout << name << " arquivo nao aberto !" << endl;
        exit(-1);
      }

      name = this->nameOut + "_cell.c++";
      fileOutCell.open(name, ios::out);
      if (!fileOutNode.is_open()) {
        cout << name << " arquivo nao aberto !" << endl;
        exit(-1);
      }
    }

    void closeOutputFile(void) {
      fileOutNode.close();
    }


    void read(Mesh &mesh, Temporal &temporal) {
      ifstream file;
      string name = this->get_nameIn();
  
      file.open(name, ios::in);
      if (!file.is_open()) {
        cout << name << " arquivo nao achado !" << endl;
        exit(-1);
      }

      this->set_nameOut(name);

      string word;
      double dValue;
      int iValue;

      while (file >> word) {

        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (word == "output") {
          file >> word;
          this->set_nameOut(word);
        }

        else if (word == "length") {
          file >> dValue;
          mesh.set_l(dValue);
        }

        else if (word == "ndiv") {
          file >> iValue;
          mesh.getCells().set_nCells(iValue);
          mesh.getNodes().set_nNodes(iValue + 1);
        }

        else if (word == "dt") {
          file >> dValue;
          temporal.set_dt(dValue);
        }

        else if (word == "nstep") {
          file >> iValue;
          temporal.set_nStep(iValue);
        }

        else if (word == "cce") {

          file >> iValue;
          mesh.getCcci().set_cceType(iValue);

          file >> dValue;
          mesh.getCcci().set_cceValue(dValue);
        }

        else if (word == "ccd") {
          file >> iValue;
          mesh.getCcci().set_ccdType(iValue);

          file >> dValue;
          mesh.getCcci().set_ccdValue(dValue);
        }

        else if (word == "initialt") {
          file >> dValue;
          mesh.getCcci().set_cciValue(dValue);
        }

        else if (word == "prop") {
          file >> dValue;
          mesh.getPropRef().set_rho(dValue);

          file >> dValue;
          mesh.getPropRef().set_cp(dValue);

          file >> dValue;
          mesh.getPropRef().set_k(dValue);
        }

        else if (word == "end") {
          break;
        }

      }

      file.close();

      mesh.alloc();
  
    }

};
