#ifndef ReadMatlab_h
#define ReadMatlab_h 1

#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

using namespace std;

class ReadMatlab {
  public:

      ReadMatlab(string nodes, string elements);

      ReadMatlab(string samename);

      virtual ~ReadMatlab();

      virtual bool execute(vector<Point> &vpoints, FaceContainer *fc);

      virtual vector<double> getBounds();

  protected:

      virtual bool points(vector<Point> &vpoints);

      virtual bool faces(FaceContainer *fc);

  private:
   
      string nodename, facename;
      vector<double> bounds;

};

inline vector<double> ReadMatlab::getBounds(){
  return bounds;
}

#endif
