#include "WriteMatlab.h"

WriteMatlab::WriteMatlab(string name){
  outname = name;
}

WriteMatlab::~WriteMatlab(){
}

FaceContainer *WriteMatlab::triangulateFaces(FaceContainer *fc){
  FaceContainer *tfc = new FaceContainer();
  for(int i=0;i<fc->length();i++){
    vector<int> fpts = fc->getFace(i)->getPoints();
    if(fpts.size()==3){
      tfc->addFace(new Face(fpts));
    }
    else{
      vector<int> tf1(3,-1);
      vector<int> tf2(3,-1);
      tf1[0]=fpts[0];
      tf1[1]=fpts[1];
      tf1[2]=fpts[3];
      tfc->addFace(new Face(tf1));
      tf2[0]=fpts[1];
      tf2[1]=fpts[2];
      tf2[2]=fpts[3];
      tfc->addFace(new Face(tf2));
    }
  }
  return tfc;
}

bool WriteMatlab::execute(vector<Point> &points, FaceContainer *fc){
  FaceContainer *tfc = triangulateFaces(fc);
  writeNodes(points);
  writeFaces(tfc);
  return true;
}

void WriteMatlab::writeNodes(vector<Point> &points){
  string outnode = "Vertex" + outname + ".txt";
  FILE *f = fopen(outnode.c_str(),"wt");
  for(int i=0;i<points.size();i++){
    fprintf(f,"  %1.7e",points[i][0]);
    fprintf(f,"  %1.7e",points[i][1]);
    fprintf(f,"  %1.7e\n",points[i][2]);
  }
  fclose(f);
}

void WriteMatlab::writeFaces(FaceContainer *fc){
  string outface = "Face" + outname + ".txt";
  FILE *f = fopen(outface.c_str(),"wt");
  for(int i=0;i<fc->length();i++){
    vector<int> aux = fc->getFace(i)->getPoints();
    for(int j=0;j<aux.size();j++)
      fprintf(f,"  %1.7e",(double)(aux[j]+1));
    fprintf(f,"\n");
  }
  
  fclose(f);
}

