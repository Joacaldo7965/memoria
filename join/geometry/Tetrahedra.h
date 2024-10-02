#ifndef Tetrahedra_h
#define Tetrahedra_h 1

#include "Element.h"

using namespace std;

class Tetrahedra : public Element{

  public:
	  Tetrahedra(vector<int> &points, int mat, int idx);

	  virtual ~Tetrahedra();

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
          //geomtry convention
	  virtual void getToStandarFormat(FileFormat *ff);

	  virtual vector<int> getPointsInFormat(FileFormat *ff);

	  virtual vector<vector <int> > getTetras();
    
    virtual unsigned int getAnsysAuxType();

};

inline int Tetrahedra::numberOfFaces(){
  return 4;
}

inline char Tetrahedra::getCharType(){
  return 'T';
}

inline int Tetrahedra::numberOfEdges(){
  return 6;
}

inline unsigned int Tetrahedra::getAnsysAuxType() {
    return 1;
}

#endif
