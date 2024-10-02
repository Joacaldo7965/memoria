#ifndef WriteM3d_h
#define WriteM3d_h 1

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../geometry/Element.h"
#include "../geometry/PointM3d.h"
#include "M3dPrinter.h"

class WriteM3d {
	
  public:

      WriteM3d(string name);

      virtual ~WriteM3d();

      virtual void execute(vector<PointM3d> &points, vector<Element *> &elements);

      virtual void writeOnlyPoints(vector<PointM3d> &points);

  protected:

      virtual void writePoints(FILE *f, vector<PointM3d> &points);

      virtual void writeElements(FILE *f, vector<Element *> &elements);

  protected:

      string outname;

};

#endif
