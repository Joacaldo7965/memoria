#ifndef ReadMeshVolume_h
#define ReadMeshVolume_h 1

#include <string.h>
#include <stdlib.h>
#include <list>
#include "../geometry/Point.h"
#include "../geometry/Tetrahedra.h"

using namespace std;

class ReadMeshVolume {
  public:

      ReadMeshVolume(string name);

      virtual ~ReadMeshVolume();

      virtual bool execute(vector<Point> &vpoints, vector<Element *> &elements);

      virtual vector<double> getBounds();

  protected:

      virtual bool points(vector<Point> &vpoints);

      virtual bool tetra(vector<Element *> &elements);

  private:
   
      FILE *file;
      string name;
      vector<double> bounds;

};

inline vector<double> ReadMeshVolume::getBounds(){
  return bounds;
}

#endif
