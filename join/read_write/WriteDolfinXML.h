#ifndef WriteDolfinXML_h
#define WriteDolfinXML_h 1

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../geometry/Element.h"
#include "../geometry/PointM3d.h"

class WriteDolfinXML {
	
  public:

      WriteDolfinXML(string name);

      virtual ~WriteDolfinXML();

      virtual void execute(vector<PointM3d> &points, vector<Element *> &elements);

  protected:

      virtual void writePoints(FILE *f, vector<PointM3d> &points);

      virtual void writeElements(FILE *f, vector<Element *> &elements);

  protected:

      string outname;

};

#endif
