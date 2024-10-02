#ifndef Hexahedra_h
#define Hexahedra_h 1

#include "Element.h"

using namespace std;

class Hexahedra : public Element{

  public:
	  Hexahedra(vector<int> &points, int mat, int idx);

	  virtual ~Hexahedra();

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

inline int Hexahedra::numberOfFaces(){
  return 6;
}

inline int Hexahedra::numberOfEdges(){
  return 12;
}

inline char Hexahedra::getCharType(){
  return 'H';
}

inline unsigned int Hexahedra::getAnsysAuxType(){
    return 3;
}

#endif
