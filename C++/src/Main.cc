#include"../include/Mesh.h"
#include"../include/Solver.h"
#include"../include/EpdSolver.h"
#include"../include/Files.h"
#include"../include/CellLoop.h"
#include"../include/RunTimes.h"
#include"../include/GerenciadoDeMemoria.h"


RunTimes times;
Memoria mem;


int main(int argc, char *argv[]) {

  Files files;
  Mesh mesh;
  Temporal temporal;
  CellHeatLoop heatCell1D;

  // ... 
  files.set_nameIn("temperatura.dat");
  files.read(mesh, temporal);
  mesh.display();
  // ............................................................................

  // ... 
  TriSolver solver(mesh.get_nCells());
  // ............................................................................

  // ... 
  mesh.grid();
  // ............................................................................

  // 
  EpdSolver epd(&mesh, &temporal, &heatCell1D, &solver);
  // ............................................................................
  
  //
  epd.init();
  // ............................................................................
  
  // ... abrindo o arquivos de saida
  files.openOutputFile();
  // ............................................................................
 
  // ...
  epd.solver(files);
  // ............................................................................ 

  // ...
  files.closeOutputFile();
  // ............................................................................

  // ...  
  cout << "Time Sist(s)   : " 
       << fixed << setprecision(4) << times.getSist() << endl
       << "Time Solver(s) : " 
       << fixed << setprecision(4) << times.getSolver() << endl
       << "Time Wres(s)   : " 
       << fixed << setprecision(4) << times.getRes() << endl;
  // ............................................................................

  return 0;

}