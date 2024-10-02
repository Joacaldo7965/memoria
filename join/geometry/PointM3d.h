#ifndef PointM3d_h
#define PointM3d_h 1

#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <stdio.h>
#include "Point.h"

using namespace std;

class PointM3d : public Point{

  public:
	  PointM3d();
	  
	  PointM3d(double x, double y, double z, int index);

	  virtual ~PointM3d();

	  virtual void setM3dProjection(Point p);

	  virtual void setM3dProjection(double vx, double vy, double vz);

	  virtual void setM3dCode(int m3dcode);

	  virtual int getM3dCode();

	  //virtual ostream& print(ostream& o);
	  virtual string print();

	  virtual void printM3d(FILE *f);

	  virtual double &operator[](int pos);

	  virtual void operator=(PointM3d p);

  protected:

	  double px,py,pz;
	  int code;

};

inline void PointM3d::setM3dCode(int m3dcode){
  code = m3dcode;
}

inline int PointM3d::getM3dCode(){
  return code;
}

#endif
