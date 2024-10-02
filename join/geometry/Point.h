#ifndef Point_h
#define Point_h 1

#include <iostream>
#include <sstream>
#include <math.h>
#include <list>
#include <vector>

class Point;
using namespace std;

class Point{
	
public:
	Point();
	
	Point(double x, double y, double z, int index);
	
	Point(double x, double y, double z);
	
	virtual ~Point();
	
	virtual void normalize();
	
	virtual double norm();
	
	virtual double dot(Point p);
	
	virtual Point cross(Point p);
	
	virtual double distance(Point p);
	
	virtual Point operator-(Point p2);
	
	virtual Point operator-();
	
	virtual Point operator+(Point p2);
	
	virtual void operator+=(Point p2);
	
	virtual void operator/=(double div);
	
	virtual double &operator[](int pos);
	
	virtual double operator[](int pos) const;
	
	virtual void operator=(Point p);
	
	virtual bool operator<(Point p);
	
	virtual Point operator*(double escalar);
	
	virtual void update(Point *point);
	
	virtual void update(Point point);
	
	virtual void setIndex(int index);
	
	virtual int getIndex();
	
	virtual void updateIndex(int newindex);
	
	virtual string print();
	
protected:
	
	double x,y,z;
	int index;
	
};

inline void Point::updateIndex(int newindex){
	index = newindex;
}

inline int Point::getIndex(){
	return index;
}

inline void Point::setIndex(int index){
	this->index=index;
}

inline void Point::update(Point *point){
	x = (*point)[0];
	y = (*point)[1];
	z = (*point)[2]; 
}

inline void Point::update(Point point){
	x = point[0];
	y = point[1];
	z = point[2]; 
}

ostream& operator<<(ostream& o,Point &p);

bool operator==(Point &p1,Point &p2);

bool operator!=(Point &p1,Point &p2); 

#endif
