#include "WriteM3d.h"

WriteM3d::WriteM3d(string name){
  outname = name;
  outname+=".m3d\0";
	  
}

WriteM3d::~WriteM3d(){
  //delete geometry;
}

void WriteM3d::writePoints(FILE *f, vector<PointM3d> &points){
  int n = points.size();
  
  fprintf(f,"%s\n","[Nodes, ARRAY1<STRING>]");
  fprintf(f,"%i\n\n",n);

  
  for(int i=0;i<n;i++){
    PointM3d p = points.at(i);
    if(p.getIndex()==-1){
      cout << "invalid index for point " << i << " in WriteM3d: -1\n";
    }
    p.printM3d(f);
  }
}

void WriteM3d::writeElements(FILE *f, vector<Element *> &elements){
  int n = elements.size();
  M3dPrinter m3dprinter;
  
  fprintf(f,"\n%s\n","[Elements, ARRAY1<STRING>]");
  fprintf(f,"%i\n\n",n);
  
  for(int i=0;i<n;i++){
    Element *element = elements.at(i);
    m3dprinter.printElement(element,f);
  }
}

void WriteM3d::writeOnlyPoints(vector<PointM3d> &points){
  FILE *f = fopen(outname.c_str(),"wt");
  
  writePoints(f,points);
  
  fclose(f);
}

void WriteM3d::execute(vector<PointM3d> &points, vector<Element *> &elements){
  FILE *f = fopen(outname.c_str(),"wt");
  
  writePoints(f,points);
  writeElements(f,elements);
  
  fclose(f);
}
