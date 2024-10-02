#include "MeshToAnsys.h"

using namespace std;

void emsg(){
  cout << "use: ./mesh2ansys input output\n";
  cout << "this will generate output.node and output.elem\n";
}

void MeshToAnsys(char** argv){
 
  ReadMeshVolume *rm;
  WriteAnsys *wa;
  
  vector<Point> points;
  vector<Element *> elements;
  
  rm = new ReadMeshVolume(argv[1]);
  rm->execute(points,elements);
  delete rm;
  
  wa = new WriteAnsys(argv[2]);
  wa->execute(points,elements);
  delete wa;
  
  for(int i=0;i<elements.size();i++)
    delete elements[i];
}

int main(int argc,char** argv){

  if(argc==3){
    MeshToAnsys(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

