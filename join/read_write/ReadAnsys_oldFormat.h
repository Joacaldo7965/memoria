#ifndef ReadAnsys_h
#define ReadAnsys_h 1

#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Hexahedra.h"
#include "../geometry/Tetrahedra.h"
#include "../geometry/Pyramid.h"
#include "../geometry/Prism.h"
#include "AnsysFormat.h"
//#include "../geometry/PointM3d.h"

using namespace std;

class ReadAnsys {
  public:

      ReadAnsys(string nodes, string elements);

      ReadAnsys(string samename);

      virtual ~ReadAnsys();

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

};

inline vector<double> ReadAnsys::getBounds(){
  return bounds;
}

#endif
