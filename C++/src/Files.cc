#include"../include/Files.h"

static void writeResLine(ofstream &file, int c1, double c2, double *cs, int nCs);

 /******************************************************************************
  *@brief     Abre os arquivos de saida                            
  *@details   Abre os arquivos de saida para escrita dos resultados. <!--
  *-->        São abertos dois arquivos.                           
  ******************************************************************************
  *@date      18/04/2021 - 25/04/2021
  *@author    Henrique C. C. de Andrade
  *******************************************************************************/
void Files::openOutputFile(void) {
  string name = this->nameOut + "_node.c++";

  fileOutNode.open(name, ios::out);
  if (!fileOutNode.is_open()) {
    cout << name << " arquivo nao aberto !" << endl;
    exit(error::fileNotFound);
  }

  name = this->nameOut + "_cell.c++";
  fileOutCell.open(name, ios::out);
  if (!fileOutNode.is_open()) {
    cout << name << " arquivo nao aberto !" << endl;
    exit(error::fileNotFound);
  }
}
/********************************************************************************/

 /******************************************************************************
  *@brief     Leitura do arquivo de entrada
  *@details   Leitura do arquivo. Neste arquivo definido as caracteristica  <!--
  *-->        da simulação               
  ******************************************************************************
  *@date      18/04/2021 - 25/04/2021
  *@author    Henrique C. C. de Andrade
  *******************************************************************************/
void Files::read(Mesh &mesh, IntTemp &intTemp) {
  ifstream file;
  string name = this->get_nameIn();

  file.open(name, ios::in);
  if (!file.is_open()) {
    cout << name << " arquivo nao achado !" << endl;
    exit(error::fileNotFound);
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
      mesh.get_cells().set_nCells(iValue);
      mesh.get_nodes().set_nNodes(iValue + 1);
    }

    else if (word == "dt") {
      file >> dValue;
      intTemp.set_dt(dValue);
    }

    else if (word == "nstep") {
      file >> iValue;
      intTemp.set_nStep(iValue);
    }

    else if (word == "cce") {
      int n = 0;
      double vValue[2];
      file >> iValue;
      mesh.get_ccci().set_cceType(iValue);
      if(iValue == typeCc::hConv){
        file >> vValue[0];
        file >> vValue[1];
        n = 2;
      }
      else {
        file >> vValue[0];
        n = 1;
      }
      mesh.get_ccci().set_cceValue(vValue, n);
    }

    else if (word == "ccd") {
      int n = 0;
      double vValue[2];
      file >> iValue;
      mesh.get_ccci().set_ccdType(iValue);

      if (iValue == typeCc::hConv) {
        file >> vValue[0];
        file >> vValue[1];
        n = 2;
      }
      else {
        file >> vValue[0];
        n = 1;
      }
      mesh.get_ccci().set_ccdValue(vValue, n);
    }

    else if (word == "initialt") {
      file >> dValue;
      mesh.get_ccci().set_cciValue(dValue);
    }

    else if (word == "prop") {
      file >> dValue;
      mesh.get_propRef().set_rho(dValue);

      file >> dValue;
      mesh.get_propRef().set_cp(dValue);

      file >> dValue;
      mesh.get_propRef().set_k(dValue);
    }

    else if (word == "end") {
      break;
    }

  }

  file.close();

  mesh.alloc();

}
/******************************************************************************/

/******************************************************************************
 *@details Escreve os resultado nodais.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void Files::resNode(Mesh &Mesh, IntTemp &intTemp) {

  writeResLine(this->fileOutNode, intTemp.get_iStep(), intTemp.get_t(),
    Mesh.get_nodes().get_u(), Mesh.get_nNodes());

}
/******************************************************************************/

/******************************************************************************
 *@details Escreve coordenada dos nós.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void Files::writeGeomNode(Mesh &mesh) {

  writeResLine(this->fileOutNode, 0, 0.0, mesh.get_nodes().get_x()
                , mesh.get_nNodes());

}
/**********************************************************************/

/******************************************************************************
 *@details  Escreve os resultado por células.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void Files::resCell(Mesh &mesh, IntTemp &intTemp) {

  writeResLine(this->fileOutCell, intTemp.get_iStep(), intTemp.get_t(),
    mesh.get_cells().get_u(), mesh.get_nCells());

}
/******************************************************************************/

/******************************************************************************
 *@details Escreve as coordenada dos centraiodes.
 ******************************************************************************
 *@date      19/04/2021 - 25/04/2021
 *@author    Henrique C. C. de Andrade
 ******************************************************************************/
void Files::writeGeomCell(Mesh &mesh) {

  writeResLine(this->fileOutCell, 0, 0.0, mesh.get_cells().get_xc()
             , mesh.get_nCells());

}
/******************************************************************************/


static void writeResLine(ofstream &file, int c1, double c2, double *cs, int nCs) {
  
  file << setw(8) << c1 << " "
    << fixed << setw(12) << setprecision(4) << c2;

  for (int i = 0; i < nCs; i++) {
    file << " " << setprecision(7) << scientific << cs[i];
  }
  file << endl;
}