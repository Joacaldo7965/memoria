#ifndef ReadMeshSurface_h
#define ReadMeshSurface_h 1

#include <string.h>
#include <stdlib.h>
#include <list>
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

using namespace std;

class ReadMeshSurface {
  public:

      ReadMeshSurface(string name);

      virtual ~ReadMeshSurface();

      virtual bool execute(vector<Point> &vpoints, FaceContainer *fc);

      virtual vector<double> getBounds();

  protected:

      virtual bool points(vector<Point> &vpoints);

      virtual bool faces(FaceContainer *fc);

  private:
   
      FILE *file;
      string name;
      vector<double> bounds;

};

inline vector<double> ReadMeshSurface::getBounds(){
  return bounds;
}

#endif
