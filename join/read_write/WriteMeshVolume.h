#ifndef WriteMeshVolume_h
#define WriteMeshVolume_h 1

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../geometry/Element.h"
#include "../geometry/Point.h"
#include "../geometry/FaceContainer.h"

class WriteMeshVolume {
	
  public:

      WriteMeshVolume(string name);

      virtual ~WriteMeshVolume();

      virtual void execute(vector<Point> &points, vector<Element *> &elements);

  protected:

      virtual void writePoints(FILE *f, vector<Point> &points);

      virtual void writeTriangles(FILE *f, vector<Element *> &elements);

      virtual void writeElements(FILE *f, vector<Element *> &elements);

  protected:

      string outname;

};

#endif
