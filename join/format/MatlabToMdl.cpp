#include "MatlabToMdl.h"

using namespace std;

void emsg(){
  cout << "use: ./matlab2mdl input output\n";
  cout << "output automatically generated with extension mdl\n";
}

void MatlabToMdl(char** argv){
  
  ReadMatlab rmat (argv[1]);
  WriteMdl wmdl (argv[2]);
  
  vector<Point> points;
  FaceContainer *fc = new FaceContainer();
  
  rmat.execute(points,fc);
  wmdl.execute(points,fc);

  cout << "> points " << points.size() << endl;
  cout << "> faces " << fc->length() << endl;

  delete fc;
  
}

int main(int argc,char** argv){

  if(argc==3){
    MatlabToMdl(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

