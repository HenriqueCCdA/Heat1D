#include"Mesh.h"
#include"Solver.h"
#include"EpdSolver.h"
#include"Files.h"
#include"CellLoop.h"

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
  
  //
  mesh.nodalInterpol();
  // ............................................................................

  // ... abrindo o arquivos de saida
  files.openOutputFile();
  mesh.writeGeomNode(files.get_fileOutNode());
  mesh.writeGeomCell(files.get_fileOutCell()); 
  // ............................................................................

  // ...
  mesh.resNode(files.get_fileOutNode(), temporal);
  mesh.resCell(files.get_fileOutCell(), temporal);
  // ............................................................................

  // ...
  epd.solver(files);
  // ............................................................................ 

  // ...
  files.closeOutputFile();
  // ............................................................................

  return 0;

}