#include "MdlToDolfinXML.h"

using namespace std;

void emsg(){
  cout << "use: ./mdl2matlab input output\n";
  cout << "output automatically generated with extension mdl\n";
}

void MdlToDolfinXML(char** argv){
  
  ReadMdl rmdl (argv[1]);
  WriteDolfinTriangleXML wdot (argv[2]);
  
  vector<Point> points;
  FaceContainer *fc = new FaceContainer();
  
  rmdl.execute(points,fc);
  wdot.execute(points,fc);

  cout << "> points " << points.size() << endl;
  cout << "> faces " << fc->length() << endl;

  delete fc;
  
}

int main(int argc,char** argv){

  if(argc==3){
    MdlToDolfinXML(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

