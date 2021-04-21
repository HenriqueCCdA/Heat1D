#include"../include/Mesh.h"
#include"../include/TriaSolver.h"
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

  // ... 
  files.set_nameIn("temperatura.dat");
  files.read(mesh, temporal);
  mesh.display();
  // ............................................................................

  // ... 
  DataStruct *data = new TriaDiagonal(mesh.get_nCells());
  Solver *solver = new TriSolver(data);
  // ............................................................................

  // ... 
  mesh.grid();
  // ............................................................................

  // ...
  CellLoop *heatCell1D = new CellHeatLoop(solver, &mesh, &temporal);
  // ............................................................................

  // 
  EpdSolver epd(&mesh, &temporal, heatCell1D, solver);
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