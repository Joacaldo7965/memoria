#ifndef JoinPoint_h
#define JoinPoint_h 1

#include "../geometry/Point.h"

using namespace std;

class JoinPoint {

  public:

	  JoinPoint(int index, int newidx);

	  virtual ~JoinPoint();

	  virtual int getIdx();

	  virtual int getNewIdx();

	  virtual void addFace(int index);
	  
	  virtual list<int> &getFaces();

	  virtual void reset();
	
  protected:

	  int idx,nidx;
	  list<int> faces;
};

inline void JoinPoint::reset(){
  faces.clear();
  nidx=-1;
  idx=-1;
}

inline list<int> &JoinPoint::getFaces(){
  return faces;
}

inline void JoinPoint::addFace(int index){
  faces.push_back(index);
}

inline int JoinPoint::getNewIdx(){
  return nidx;
}

inline int JoinPoint::getIdx(){
  return idx;
}

#endif
