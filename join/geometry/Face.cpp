#include "Face.h"

Face::Face(vector<int> &apoints){
	int pn=apoints.size();
	color=" 1 1 1 ";
	minindex=-1;
	points.reserve(pn);
	for(int i=0;i<pn;i++){
		addPoint(apoints[i]);
	}
}

Face::~Face(){

}

void Face::addPoint(int index){
  if(points.capacity()==0)
    return;
  if(index<minindex || minindex==-1)
    minindex=index;
  points.push_back(index);
}

void Face::printFace(FILE *f){
  for(int i=0;i<points.size();i++){
    fprintf(f,"%i ",points[i]);
  }
}

void Face::replacePoints(vector<int> &newpts){
	points.clear();
	points.reserve(newpts.size());
	for (int i=0; i<(int)newpts.size(); i++) {
		addPoint(newpts[i]);
	}
}

list<vector <int> > Face::getTriangles(){
  list<vector <int> > triangles;
  for(int i=2;i<points.size();i++){
    vector<int> t (3,-1);
    t[0] = points[0];
    t[1] = points[i-1];
    t[2] = points[i];
    triangles.push_back(t);
  }
  return triangles;
}

void Face::printTriangles(FILE *f){
  for(int i=2;i<points.size();i++){
    fprintf(f,"%i ",points[0]);
    fprintf(f,"%i ",points[i-1]);
    fprintf(f,"%i ",points[i]);
    fprintf(f,"%s\n","0 0 0");
  }
}

bool Face::hasPoint(int index){
  for(int i=0;i<points.size();i++)
    if(points[i]==index)
      return true;
  return false;
}

void Face::replacePoint(int oldp, int newp){
  for(int i=0;i<points.size();i++)
    if(points[i]==oldp)
      points[i]=newp;
}

void Face::print(){
  cout << points.size() << " " << elements.size();
}


ostream& operator<<(ostream& o,Face &f){
  vector<int> p = f.getPoints();
  int n = p.size();
  o << n;
  for(int i=0;i<n;i++){
    o << " " << p.at(i);
  }
  //o << f.getColor();
  //o << " " << f.numberOfElements();
  return o;
}

bool operator==(Face &f1,Face &f2){
  int i,n;
  vector<int> p = f2.getPoints();
  if(f1.numberOfPoints()!=f2.numberOfPoints())
    return false;
  n = p.size();
  for(i=0;i<n;i++)
    if(!f1.hasPoint(p.at(i)))
      return false;
  return true;
}

