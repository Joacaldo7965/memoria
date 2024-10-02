#include "WriteMeshVolume.h"

WriteMeshVolume::WriteMeshVolume(string name){
  outname = name;
  outname+=".mesh";
	  
}

WriteMeshVolume::~WriteMeshVolume(){

}

void WriteMeshVolume::writePoints(FILE *f, vector<Point> &points){
  int n = points.size();
  
  fprintf(f,"MeshVersionFormatted\n1\n\nDimension\n3\n\nVertices");
  fprintf(f,"\n%i\n\n",n);

  
  for(int i=0;i<n;i++){
    Point p = points.at(i);
    if(p.getIndex()==-1){
      cout << "invalid index for point " << i << " in WriteMeshVolume: -1\n";
    }
    fprintf(f,"%+1.8E %1.8E %1.8E %i\n",p[0],p[1],p[2],0);
  }
}

void WriteMeshVolume::writeTriangles(FILE *f, vector<Element *> &elements){
  FaceContainer fc;
  list<int> surf;
  list<int>::iterator iter;

  for(int i=0;i<elements.size();i++){
    int nf = elements[i]->numberOfFaces();
    for(int j=0;j<nf;j++){
      vector<int> fpts = elements[i]->getFacePoints(j);
      Face *f = new Face(fpts);
      int fn = fc.addFace(f);
      fc.getFace(fn)->addElement(i);
    }
  }
  for(int i=0;i<fc.length();i++){
    if(fc.getFace(i)->numberOfElements()==1)
      surf.push_back(i);
  }
  fprintf(f,"\nTriangles\n%i\n\n",(int)surf.size());
  for(iter=surf.begin();iter!=surf.end();iter++){
    vector<int> fp = fc.getFace(*iter)->getPoints();
    fprintf(f,"%i %i %i 0\n",fp[0]+1,fp[1]+1,fp[2]+1);
  }
}

void WriteMeshVolume::writeElements(FILE *f, vector<Element *> &elements){
  int n = elements.size();
  
  fprintf(f,"\n%s\n%i\n\n","Tetrahedra",n);
  
  for(int i=0;i<n;i++){
    vector<int> epts = elements.at(i)->getPoints();
    fprintf(f,"%i %i %i %i 0\n",epts[0]+1,epts[1]+1,epts[2]+1,epts[3]+1);
  }
}

void WriteMeshVolume::execute(vector<Point> &points, vector<Element *> &elements){
  FILE *f = fopen(outname.c_str(),"wt");
  
  writePoints(f,points);
  writeTriangles(f,elements);
  writeElements(f,elements);
  
  fclose(f);
}
