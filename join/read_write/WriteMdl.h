#ifndef WriteMdl_h
#define WriteMdl_h 1

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../geometry/FaceContainer.h"
#include "../geometry/Point.h"

class WriteMdl {
	
  public:

      WriteMdl(string name);

      virtual ~WriteMdl();

      //wirte a mdl file with square and trinagle faces
      virtual void execute(vector<Point> &points, FaceContainer *fc);

      //wirte a mdl file where non triangular faces are triangulated
      virtual void writeWithTriangleFaces(vector<Point> &points, FaceContainer *fc);

      //write only the points in a mdl format
      virtual void writeOnlyPoints(vector<Point> &points);

  protected:

      virtual void writeHead(FILE *f);

      virtual void writePoints(FILE *f, vector<Point> &points);

      virtual void writeFaces(FILE *f, FaceContainer *fc);
      
      virtual void writeTriangleFaces(FILE *f, FaceContainer *fc);

  protected:

      string outname;

};

#endif
