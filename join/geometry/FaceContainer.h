#ifndef FaceContainer_h
#define FaceContainer_h 1

#include <iostream>
#include <vector>
#include <list>
#include "Face.h"

using namespace std;

class FaceContainer{

  public:
	  FaceContainer();

	  virtual ~FaceContainer();

	  virtual Face *getFace(int index);

	  virtual int length();

	  virtual int addFace(Face *f);

	  virtual int getFaceIndex(Face *f);
	  
	  virtual int getIndex(Face *f);

	  virtual void updatePointIndex(int oldp, int newp,list<int> &fs);

	  virtual void clear();

  protected:

	  virtual int outOfBoundary(int index);

  protected:

	  vector<Face *> facesvec;
	  int size, hashingsize;
	  vector<list <int> > hashing;
	  list <int>::iterator hashiter;

};

inline void FaceContainer::clear(){
  for(int i=0;i<size;i++)
    delete facesvec[i];
  facesvec.clear();
  size=0;
  hashingsize=0;
  hashing.clear();
}

#endif
