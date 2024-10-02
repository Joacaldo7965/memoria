#include "AnsysToMesh.h"

using namespace std;

void emsg(){
  cout << "use: ./ansys2mesh input output\n";
  cout << "do not add .mesh at the end of output file\n";
  cout << " >Important note: this process will fail if ansys\n";
  cout << "  input mesh do not containt only tetrahedra elements\n";
}

void ansysToMesh(char** argv){
  
  ReadAnsys *ra;
  WriteMeshVolume *wm;
  
  vector<Point> points;
  vector<Element *> elements;
  
  ra = new ReadAnsys(argv[1]);
  ra->execute(points,elements);
  delete ra;
  
  wm = new WriteMeshVolume(argv[2]);
  wm->execute(points,elements);
  delete wm;
  
  for(int i=0;i<elements.size();i++)
    delete elements[i];
}

int main(int argc,char** argv){

  if(argc==3){
    ansysToMesh(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

