#ifndef Face_h
#define Face_h 1

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "Point.h"

using namespace std;

class Face{

  public:
	  
	Face(vector<int> &apoints);
	  
	virtual ~Face();

	virtual vector<int> &getPoints();

	virtual int numberOfPoints();

	virtual bool hasPoint(int index);

	virtual int getMinIndex();

	virtual string getColor();

	virtual void setColor(string color);

	virtual void replacePoint(int oldp, int newp);
	
	virtual void replacePoints(vector<int> &newpts);

	virtual void printTriangles(FILE *f);

	virtual list<vector <int> > getTriangles();

	virtual void printFace(FILE *f);

	virtual int numberOfTriangles();

	virtual void addElement(int idx);
	
	virtual list<int> &getElements();
	
	virtual void clearElements();

	virtual int numberOfElements();

	//debugging
	virtual void print();

  protected:

	virtual void addPoint(int index);

  protected:

	vector<int> points;
	list<int> elements;
	int minindex;
	string color;

};

inline int Face::numberOfElements(){
	return elements.size();
}

inline void Face::addElement(int idx){
	list<int>::iterator iter;
	bool found=false;
	for (iter=elements.begin(); iter!=elements.end(); iter++) {
		if ((*iter)==idx) {
			found=true;
			break;
		}
	}
	if (!found) {
		elements.push_back(idx);
	}
}

inline list<int> &Face::getElements(){
	return elements;
}

inline void Face::clearElements(){
	elements.clear();
}

inline int Face::numberOfTriangles(){
  return points.size()-2;
}

inline vector<int> &Face::getPoints(){
  return points;
}

inline int Face::numberOfPoints(){
  return points.size();
}

inline int Face::getMinIndex(){
  return minindex;
}

inline string Face::getColor(){
  return color;
}

inline void Face::setColor(string color){
  this->color=color;
}

ostream& operator<<(ostream& o,Face &f);

bool operator==(Face &f1,Face &f2);

#endif
