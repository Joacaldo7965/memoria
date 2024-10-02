#include "M3dToAnsys.h"

using namespace std;

void emsg(){
  cout << "use: ./m3d2ansys file.m3d output\n";
  cout << "output will be written with extensions: node & elem\n";
}

vector<Point> getAnsysPoints(vector<PointM3d> &m3dpoints){
  vector<Point> aux;
  int n = m3dpoints.size();
  aux.reserve(n);

  for(int i=0;i<n;i++){
    aux.push_back(PointM3d (m3dpoints[i][0],
			    m3dpoints[i][1],
			    m3dpoints[i][2],
		    	    m3dpoints[i].getIndex()));
  }
  return aux;
}

void m3dToAnsys(char** argv){
  
  ReadM3d *rm;
  WriteAnsys *wa;
  
  vector<PointM3d> m3dpoints;
  vector<Point> ansyspoints;
  vector<Element *> elements;
  
  rm = new ReadM3d(argv[1]);
  rm->execute(m3dpoints,elements);
  delete rm;
  
  ansyspoints = getAnsysPoints(m3dpoints);
  
  wa = new WriteAnsys(argv[2]);
  wa->execute(ansyspoints,elements);
  delete wa;
  
  for(int i=0;i<elements.size();i++)
    delete elements[i];
}

int main(int argc,char** argv){

  if(argc==3){
    m3dToAnsys(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

