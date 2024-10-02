#ifndef ReadPascal_h
#define ReadPascal_h 1

#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

using namespace std;

class ReadPascal {
  public:

      ReadPascal(string nodes, string elements);

      ReadPascal(string samename);

      virtual ~ReadPascal();

      virtual bool execute(vector<Point> &vpoints, FaceContainer *fc);

      virtual vector<double> getBounds();

      //virtual vector<PointM3d> getM3dPoints(vector<Point> &ansyspoints);

  protected:

      virtual bool points(vector<Point> &vpoints);

      virtual bool elements(FaceContainer *fc);

      virtual vector<int> removeRepeated(vector<int> &all);

  private:
   
      string nodename, elemname;
      vector<double> bounds;
      int offset;

};

inline vector<double> ReadPascal::getBounds(){
  return bounds;
}

#endif
