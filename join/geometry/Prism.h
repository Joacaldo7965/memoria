#ifndef Prism_h
#define Prism_h 1

#include "Element.h"

using namespace std;

class Prism : public Element{

  public:
	  Prism(vector<int> &points, int mat, int idx);

	  virtual ~Prism();

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

inline int Prism::numberOfFaces(){
  return 5;
}

inline char Prism::getCharType(){
  return 'R';
}

inline int Prism::numberOfEdges(){
  return 9;
}

inline unsigned int Prism::getAnsysAuxType() {
    return 2;
}

#endif
