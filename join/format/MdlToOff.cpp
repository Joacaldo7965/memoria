#include "MdlToOff.h"

using namespace std;

void emsg(){
  cout << "use: ./mdl2off input output\n";
  cout << "output automatically generated with extension mdl\n";
}

void MdlToOff(char** argv){
  
  ReadMdl rmdl (argv[1]);
  WriteOff woff (argv[2]);
  
  vector<Point> points;
  FaceContainer *fc = new FaceContainer();
  
  rmdl.execute(points,fc);
  woff.execute(points,fc);

  cout << "> points " << points.size() << endl;
  cout << "> faces " << fc->length() << endl;

  delete fc;
  
}

int main(int argc,char** argv){

  if(argc==3){
    MdlToOff(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

