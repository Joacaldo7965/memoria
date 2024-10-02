#ifndef WriteDolfinTriangleXML_h
#define WriteDolfinTriangleXML_h 1

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../geometry/FaceContainer.h"
#include "../geometry/Point.h"

class WriteDolfinTriangleXML {
	
  public:

      WriteDolfinTriangleXML(string name);

      virtual ~WriteDolfinTriangleXML();

      virtual void execute(vector<Point> &points, FaceContainer* fc);

  protected:

      virtual void writePoints(FILE *f, vector<Point> &points);

      virtual void writeElements(FILE *f, FaceContainer* fc);

  protected:

      string outname;

};

#endif
