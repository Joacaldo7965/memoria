#ifndef WriteMatlab_h
#define WriteMatlab_h 1

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

class WriteMatlab {
  public:

      WriteMatlab(string name);

      virtual ~WriteMatlab();

      virtual bool execute(vector<Point> &points, FaceContainer *fc);
      
  protected:
  
      virtual void writeNodes(vector<Point> &points);
      
      virtual void writeFaces(FaceContainer *fc);

      virtual FaceContainer *triangulateFaces(FaceContainer *fc);

  protected:

      string outname;

};

#endif
