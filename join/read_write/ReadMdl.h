#ifndef ReadMdl_h
#define ReadMdl_h 1

#include <string.h>
#include <stdlib.h>
#include <list>
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

using namespace std;

class ReadMdl {
  public:

      ReadMdl(string name);

      virtual ~ReadMdl();

      virtual bool execute(vector<Point> &vpoints, FaceContainer *fc);

      virtual vector<double> getBounds();

  protected:

      virtual bool points(vector<Point> &vpoints);

      virtual bool faces(FaceContainer *fc);

      virtual void readFaces(int type, int cant, FaceContainer *fc);

  private:
   
      FILE *file;
      string name;
      vector<double> bounds;

};

inline vector<double> ReadMdl::getBounds(){
  return bounds;
}

#endif
