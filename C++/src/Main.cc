#include"Mesh.h"
#include"Solver.h"
#include"EpdSolver.h"
#include"Files.h"

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
  TriSolver solver(mesh.get_nCells());
  // ............................................................................

  // ... 
  mesh.grid();
  // ............................................................................

  // 
  EpdSolver epd(&mesh, &temporal);
  // ............................................................................
  
  //
  epd.init();
  // ............................................................................
  
  //
  mesh.nodalInterpol();
  // ............................................................................

  //abrindo o aruivos de saida
  files.openOutputFile();
  mesh.res_node(files.get_fileOutNode());
  files.closeOutputFile();
  // ............................................................................

  return 0;

}