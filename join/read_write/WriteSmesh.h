#ifndef WriteSmesh_h
#define WriteSmesh_h 1

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../geometry/FaceContainer.h"
#include "../geometry/Point.h"

class WriteSmesh {
	
  public:

      WriteSmesh(string name);

      virtual ~WriteSmesh();

      virtual void execute(vector<Point> &points, FaceContainer *fc);


  protected:

      virtual void writePoints(FILE *f, vector<Point> &points);

      virtual void writeTriangleFaces(FILE *f, FaceContainer *fc);

  protected:

      string outname;

};

#endif
