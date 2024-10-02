#include "M3dToDolfinXML.h"

using namespace std;

void emsg(){
  cout << "use: ./m3d2dolfinXML file.m3d output\n";
  cout << "output will be written with extensions: xml\n";
}

void m3dToDolfinXML(char** argv){
  
  ReadM3d *rm;
  WriteDolfinXML *wd;
  
  vector<PointM3d> m3dpoints;
  vector<Element *> elements;
  
  rm = new ReadM3d(argv[1]);
  rm->execute(m3dpoints,elements);
  delete rm;
  
  wd = new WriteDolfinXML(argv[2]);
  wd->execute(m3dpoints,elements);
  delete wd;
  
  for(int i=0;i<elements.size();i++)
    delete elements[i];
}

int main(int argc,char** argv){

  if(argc==3){
    m3dToDolfinXML(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

