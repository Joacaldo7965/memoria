#include "M3dPrinter.h"

M3dPrinter::M3dPrinter(){ 

}

M3dPrinter::~M3dPrinter(){

}

void M3dPrinter::printElement(Element *element, FILE *f){
  fprintf(f,"%c ",element->getCharType());
  for(int i=0;i<element->numberOfPoints();i++)
    fprintf(f,"%i ",element->getPoint(i));
  fprintf(f,"%s\n","1000.0 0.45 1.0");
}

