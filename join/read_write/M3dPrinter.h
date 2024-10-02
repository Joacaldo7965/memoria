#ifndef M3dPrinter_h
#define M3dPrinter_h 1

#include "../geometry/Hexahedra.h"
#include "../geometry/Prism.h"
#include "../geometry/Pyramid.h"
#include "../geometry/Tetrahedra.h"

using namespace std;

class M3dPrinter {

  public:
	  M3dPrinter();

	  virtual ~M3dPrinter();

	  virtual void printElement(Element *element, FILE *f);

};

#endif
