#ifndef WriteAnsys_h
#define WriteAnsys_h 1

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include "../geometry/Point.h"
#include "../geometry/Element.h"
#include "AnsysFormat.h"

class WriteAnsys {
  public:

      WriteAnsys(string name);

      virtual ~WriteAnsys();

      virtual bool execute(vector<Point> &points, vector<Element *> &elements);
      
  protected:
  
      virtual void writeNodes(vector<Point> &points);
      
      virtual void writeElements(vector<Element *> &elements);

  protected:

      string outname;

};

#endif
