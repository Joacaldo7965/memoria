#include "PointM3d.h"

PointM3d::PointM3d(){
  x=y=z=0;
  px=py=pz=0;
  index=-1;
  //default m3d code 1: free point.
  code=1;
}

PointM3d::PointM3d(double x, double y, double z, int index) : Point(x,y,z,index){
  px=py=pz=0;
  //default m3d code 1: free point.
  code=1;
}

PointM3d::~PointM3d(){

}

void PointM3d::setM3dProjection(double vx, double vy, double vz){
  px = vx;
  py = vy;
  pz = vz;
}

void PointM3d::setM3dProjection(Point point){
  px = point[0];
  py = point[1];
  pz = point[2];  
}

void PointM3d::operator=(PointM3d p){
  x  = p[0];
  y  = p[1];
  z  = p[2];
  px = p[3];
  py = p[4];
  pz = p[5];
  code = p.getM3dCode();
  index = p.getIndex();
}

double &PointM3d::operator[](int pos){
  switch(pos){
    case 0:
     return x;
    case 1:
     return y;
    case 2:
     return z;
    case 3:
     return px;
    case 4:
     return py;
    default:
     return pz;
  }
}

string PointM3d::print(){
  string out = Point::print();
  ostringstream o;
  
  out += " pro ";
  
  o << px << " " << " " << py << " " << pz;
  out += o.str();
  return out;
}

/*ostream& PointM3d::print(ostream& o){
  o << index << " ";
  o << x << " ";
  o << y << " ";
  o << z << " pro: ";
  o << px << " ";
  o << py << " ";
  o << pz;
  return o;
}*/

void PointM3d::printM3d(FILE *f){
  fprintf(f,"%i",code);
  fprintf(f," %+1.8E",x);
  fprintf(f," %+1.8E",y);
  fprintf(f," %+1.8E",z);
  if(code > 1){
    fprintf(f," %+1.8E",px);
    fprintf(f," %+1.8E",py);
    fprintf(f," %+1.8E",pz);
  }
  fprintf(f,"\n");
}
