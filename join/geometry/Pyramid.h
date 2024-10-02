#ifndef Pyramid_h
#define Pyramid_h 1

#include "Element.h"

using namespace std;

class Pyramid : public Element{

  public:
	  Pyramid(vector<int> &points, int mat, int idx);

	  virtual ~Pyramid();

	  virtual int numberOfFaces();

	  virtual int numberOfEdges();

	  virtual char getCharType();

	  virtual vector<int> getFacePoints(int index);

	  //returns the two nodes in edge index
	  virtual vector<int> getEdge(int index);

	  //returns a list with nodes connected to index
          virtual vector<int> getEdges(int index);

	  //The two following methods will allow to pass from any
          //possible format of IOFile to the standar M3d used in
          //geomtry convention.
	  virtual void getToStandarFormat(FileFormat *ff);

	  virtual vector<int> getPointsInFormat(FileFormat *ff);

	  virtual vector<vector <int> > getTetras();
    
    virtual unsigned int getAnsysAuxType();

};

inline int Pyramid::numberOfFaces(){
  return 5;
}

inline char Pyramid::getCharType(){
  return 'P';
}

inline int Pyramid::numberOfEdges(){
  return 8;
}

inline unsigned int Pyramid::getAnsysAuxType() {
    return 4;
}

#endif
