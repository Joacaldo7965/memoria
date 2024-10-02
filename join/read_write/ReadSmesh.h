#ifndef ReadSmesh_h
#define ReadSmesh_h 1

#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Tetrahedra.h"

using namespace std;

class ReadSmesh {
  public:

      ReadSmesh(string nodes, string elements);

      ReadSmesh(string samename);

      virtual ~ReadSmesh();

      virtual bool execute(vector<Point> &vpoints, vector<Element *> &velements);

      virtual vector<double> getBounds();

      //virtual vector<PointM3d> getM3dPoints(vector<Point> &ansyspoints);

  protected:

      virtual bool points(vector<Point> &vpoints);

      virtual bool elements(vector<Element *> &elements);

      virtual vector<int> removeRepeated(vector<int> &all);

  private:
   
      string nodename, elemname;
      vector<double> bounds;
    int offset;

};

inline vector<double> ReadSmesh::getBounds(){
  return bounds;
}

#endif
