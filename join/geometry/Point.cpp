#include "Point.h"
#include "Element.h"

Point::Point(){
	x=y=z=0;
	index=-1;
}

Point::Point(double x, double y, double z, int index){
	this->x=x;
	this->y=y;
	this->z=z;
	this->index = index;
}

Point::Point(double x, double y, double z){
	this->x=x;
	this->y=y;
	this->z=z;
	index = -1;
}

Point::~Point(){
	
}

Point Point::cross(Point p){
	Point ret;
	ret[0]=y*p[2] - z*p[1];
	ret[1]=z*p[0] - x*p[2];
	ret[2]=x*p[1] - y*p[0];
	return ret;
}

double Point::dot(Point p){
	return x*p[0] + y*p[1] + z*p[2];
}

double Point::distance(Point p){
	return ((*this)-p).norm();
}

void Point::normalize(){
	double nor=norm();
	if(nor!=0){
		x/=nor;
		y/=nor;
		z/=nor;
	}
	else
		x=y=z=0;
}

double Point::norm(){
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

string Point::print(){
	ostringstream o;
	string out;
	
	o << index << " ";
	o << x << " ";
	o << y << " ";
	o << z;
	
	out = o.str();
	return out;
}

ostream& operator<<(ostream& o,Point &p){
	o << p.print().c_str();
	return o;
}

bool operator==(Point &p1,Point &p2){
	Point p=p1-p2;
	double dx=p[0],dy=p[1],dz=p[2];
	double epsilon=0.0001;
	if(dx<0) dx*=-1;
	if(dy<0) dy*=-1;
	if(dz<0) dz*=-1;
	if(dx>epsilon)
		return false;
	if(dy>epsilon)
		return false;
	if(dz>epsilon)
		return false;
	return true;
}

bool operator!=(Point &p1,Point &p2){
	return !(p1==p2);
}

Point Point::operator-(){
	Point p;
	p[0]=-x;
	p[1]=-y;
	p[2]=-z;
	return p;
}

Point Point::operator-(Point p2){
	Point p;
	p[0]=x-p2[0];
	p[1]=y-p2[1];
	p[2]=z-p2[2];
	return p;
}

Point Point::operator+(Point p2){
	Point p;
	p[0]=x+p2[0];
	p[1]=y+p2[1];
	p[2]=z+p2[2];
	return p;
}

void Point::operator/=(double div){
	x/=div;
	y/=div;
	z/=div;
}

void Point::operator+=(Point p2){
	x+=p2[0];
	y+=p2[1];
	z+=p2[2];
}

void Point::operator=(Point p){
	x=p[0];
	y=p[1];
	z=p[2];
	index = p.getIndex();
}

double &Point::operator[](int pos){
	if(pos==0)
		return x;
	if(pos==1)
		return y;
	return z;
}

double Point::operator[](int pos) const{
	if(pos==0)
		return x;
	if(pos==1)
		return y;
	return z;
}

bool Point::operator<(Point p){
	if(getIndex() < p.getIndex())
		return true;
	return false;
}

Point Point::operator*(double escalar){
	Point ret;
	ret[0] = x*escalar;
	ret[1] = y*escalar;
	ret[2] = z*escalar;
	return ret;
}

