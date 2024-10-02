#include "ReadOff.h"

ReadOff::ReadOff(){
  bounds.assign(6,-1);  
}

ReadOff::~ReadOff(){

}

bool ReadOff::readHeader(){
  char word [256];
  bool skel = false;
  while(1){
    if(fscanf(file,"%s",word) == EOF)
      return false;
    if(!strcmp(word,"OFF\0"))
      break;
    if(!strcmp(word,"SKEL\0")){
      break;
      skel = true;
    }
  }
  //read number of points  
  fscanf(file,"%i",&np);
  //read number of faces
  fscanf(file,"%i",&nf);
  if(!skel)
    //read number of edges [info not needed].
    fscanf(file,"%s",word);
  return true;
}


bool ReadOff::readPoints(vector<Point> &points){
  char word [256];
  double x,y,z;
  
  points.reserve(np);

  if(np<=0){
    cerr << "warning: no nodes were found\n";
    return true;
  }
  
  fscanf(file,"%s",word);
  x=atof(word);
  fscanf(file,"%s",word);
  y=atof(word);
  fscanf(file,"%s",word);
  z=atof(word);
  points.push_back(Point(x,y,z,0));
  fgets(word,256,file);
  bounds[0]=bounds[3]=x;
  bounds[1]=bounds[4]=y;
  bounds[2]=bounds[5]=z;

  for(int i=1;i<np;i++){
    fscanf(file,"%s",word);
    x=atof(word);
    fscanf(file,"%s",word);
    y=atof(word);
    fscanf(file,"%s",word);
    z=atof(word);
    points.push_back(Point(x,y,z,i));
    fgets(word,256,file);
    if(bounds[0]>x)
      bounds[0]=x;
    else if(bounds[3]<x)
      bounds[3]=x;
    if(bounds[1]>y)
      bounds[1]=y;
    else if(bounds[4]<y)
      bounds[4]=y;
    if(bounds[2]>z)
      bounds[2]=z;
    else if(bounds[5]<z)
      bounds[5]=z;
  }
  return true;
}

bool ReadOff::readFaces(FaceContainer *fc){
  char word[256];
  int npf,pi;
  vector<int> indexes;
  
  for(int i=0;i<nf;i++){
    fscanf(file,"%i",&npf);
    indexes.clear();
    indexes.reserve(npf);
    
    for(int j=0;j<npf;j++){
      fscanf(file,"%i",&pi);
      indexes.push_back(pi);
    }
    fgets(word,256,file);
    fc->addFace(new Face(indexes));
  }
  return true;
}

bool ReadOff::execute(char *name, vector<Point> &points,FaceContainer *fc){
  
  file=fopen(name,"r");
  
  if(file==NULL){
    cout << "Error while trying to read: \"";
    cout << name << "\"\n";
    return false;
  }
  
  //Analyze the header
  if(!readHeader()){
    cout << " not a .geomview file [header]\n";
    fclose(file);
    return false;
  }
  if(!readPoints(points)){
    cout << " not a .geomview file [points]\n";
    fclose(file);
    return false;
  }
  
  if(!readFaces(fc)){
    cout << " not a .geomview file [faces]\n";
    fclose(file);
    return false;
  }

  fclose(file);
  
  return true;
}
