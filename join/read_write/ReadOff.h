#ifndef ReadOff_h
#define ReadOff_h 1

#include <string.h>
#include <stdlib.h>
#include <list>
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

using namespace std;

class ReadOff {
  public:

      ReadOff();

      virtual ~ReadOff();

      virtual bool execute(char *name, vector<Point> &points,
		      FaceContainer *fc);

      virtual vector<double> getBounds();

  protected:

      virtual bool readPoints(vector<Point> &points);

      virtual bool readFaces(FaceContainer *fc);

      virtual bool readHeader();

  private:
   
      FILE *file;
      int np,nf;
      vector<double> bounds;

};

inline vector<double> ReadOff::getBounds(){
  return bounds;
}
#endif
