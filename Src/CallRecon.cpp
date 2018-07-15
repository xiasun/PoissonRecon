#include <iostream>
#include <vector>
#include <string>
#include <string.h>

#include "Ply.h"
#include "PoissonRecon.h"

using namespace std;

struct Argument {
  string inPath;
  string outPath;
  int depth = 10;
  bool density = false;
};

int simpleCmdParse( int argc, char* argv[], Argument &arg );
int argValidate( Argument &arg );

int main( int argc , char* argv[] ) {
  Argument arg;
  const static unsigned int Dim = 3;

  // parse and validate cmd arguments, for demo purpose
  if (!simpleCmdParse(argc, argv, arg)) {
    return 1;
  }
  if (!argValidate(arg)) {
    return 1;
  }

  // construct points and normals data structures
  vector<vector<float>> pts;
  Execute< float >(pts, IsotropicUIntPack< Dim , FEMDegreeAndBType< 1 , BOUNDARY_FREE >::Signature >() );

  return 0;
}

int simpleCmdParse( int argc, char* argv[], Argument &arg ) {
  for (int i = 1; i < argc; ++i) {
    if (!strcmp(argv[i], "--in") && i + 1 < argc) {
      arg.inPath = argv[i + 1];
      ++i;
      continue;
    }
    if (!strcmp(argv[i], "--out") && i + 1 < argc) {
      arg.outPath = argv[i + 1];
      ++i;
      continue;
    }
    if (!strcmp(argv[i], "--depth") && i + 1 < argc) {
      arg.depth = atoi(argv[i + 1]);
      ++i;
      continue;
    }
    if (!strcmp(argv[i], "--density")) {
      arg.density = true;
      continue;
    }
    cout << "Wrong input arguments!" << endl
      << "Should contain at least: " << endl 
      << "------" << endl
      << "--in (input file path)" << endl 
      << "--out (output file path)" << endl
      << "--depth (octree depth, default 10)" << endl
      << "--density (whether to have density, default true)" << endl
      << "------" << endl
      << "For example: " << endl
      << "./CallRecon --in Data/sphere_points_cut.xyz --out Data/sphere_reconmesh_cut.ply --depth 12 --density" << endl;
    return 0;
  }
  return 1;
}

int argValidate( Argument &arg ) {
  if (arg.inPath.size() == 0) {
    cout << "--in (input file path) required" << endl;
    return 0;
  }
  if (arg.outPath.size() == 0) {
    cout << "--out (output file path) required" << endl;
    return 0;
  }
  return 1;
}
