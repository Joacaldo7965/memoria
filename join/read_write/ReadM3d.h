#ifndef ReadM3d_h
#define ReadM3d_h 1

#include <string.h>
#include <stdlib.h>
#include <list>
#include "../geometry/PointM3d.h"
#include "../geometry/Hexahedra.h"
#include "../geometry/Tetrahedra.h"
#include "../geometry/Pyramid.h"
#include "../geometry/Prism.h"

using namespace std;

class ReadM3d {
  public:

      ReadM3d(string name);

      virtual ~ReadM3d();

      virtual bool execute(vector<PointM3d> &vpoints, vector<Element *> &velements);

      virtual vector<double> getBounds();

  protected:

      virtual bool points(vector<PointM3d> &vpoints);

      virtual bool elements(vector<Element *> &velements);

  private:
   
      FILE *file;
      string name;    
      vector<double> bounds;

};

inline vector<double> ReadM3d::getBounds(){
  return bounds;
}

#endif
