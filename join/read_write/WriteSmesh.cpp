#include "WriteSmesh.h"

WriteSmesh::WriteSmesh(string name){
  outname = name;
  outname+=".smesh\0";
	  
}

WriteSmesh::~WriteSmesh(){
  //delete geometry;
}

void WriteSmesh::writePoints(FILE *f, vector<Point> &points){
  int n = points.size();
  fprintf(f,"%s\n","#points");
  fprintf(f,"%i 3 0 0\n\n",n);
  
  for(int i=0;i<n;i++){
    Point p = points.at(i);
    fprintf(f,"%i",i+1);
    fprintf(f," %+1.8E",p[0]);
    fprintf(f," %+1.8E",p[1]);
    fprintf(f," %+1.8E\n",p[2]);
  }
}


void WriteSmesh::writeTriangleFaces(FILE *f, FaceContainer *fc){
  int n = fc->length(),triangulated=0;
  list<vector <int> >::iterator iter;
  
  //count the number of triangles.
  for(int i=0;i<n;i++){
    Face *f = fc->getFace(i);
    triangulated += f->numberOfTriangles();
  }

  fprintf(f,"\n%s\n","#faces");
  fprintf(f,"%i\n\n",triangulated);
  
  for(int i=0;i<n;i++){
    list<vector <int> > tri = fc->getFace(i)->getTriangles();
    for(iter = tri.begin();iter!=tri.end();iter++){
      vector<int> t = *iter;
      fprintf(f,"3");
      for(int i=0;i<3;i++){
        fprintf(f," %i",t[i]+1);
      }
      fprintf(f,"\n");
    }    
  }
  fprintf(f,"\n#holes\n0\n\n#regions\n0\n");
}

void WriteSmesh::execute(vector<Point> &points, FaceContainer *fc){
  FILE *f = fopen(outname.c_str(),"wt");
  
  writePoints(f,points);
  writeTriangleFaces(f,fc);
  
  fclose(f);
}

