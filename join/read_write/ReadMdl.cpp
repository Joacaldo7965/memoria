#include "ReadMdl.h"

ReadMdl::ReadMdl(string name){
  this->name=name;
  bounds.assign(6,-1);
}

ReadMdl::~ReadMdl(){

}

bool ReadMdl::points(vector<Point> &vpoints){
  char word [256];
  int cant;
  double x,y,z;
  
  while(1){
    if(fscanf(file,"%s",word)==EOF)
      return 0;
    if(!strcmp(word,"ARRAY1<POINT3D>]\0"))
      break;
  }
  fscanf(file,"%i",&cant);

  if(cant<=0){
    cerr << "warning: no nodes were found\n";
    return true;
  }

  vpoints.reserve(cant);

  //read the first point (to initialize the bounds)
  fscanf(file,"%s",word);
  x=atof(word);
  fscanf(file,"%s",word);
  y=atof(word);
  fscanf(file,"%s",word);
  z=atof(word);
  Point p (x,y,z,0);
  vpoints.push_back(p);
  bounds[0]=bounds[3]=x;
  bounds[1]=bounds[4]=y;
  bounds[2]=bounds[5]=z;
  
  for(int i=1;i<cant;i++){
    fscanf(file,"%s",word);
    x=atof(word);
    fscanf(file,"%s",word);
    y=atof(word);
    fscanf(file,"%s",word);
    z=atof(word);
    Point p (x,y,z,i);
    vpoints.push_back(p);
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

bool ReadMdl::faces(FaceContainer *fc){
  char word [256];
  int cant;
  
  while(1){
    if(fscanf(file,"%s",word) == EOF)
      break;
  
    if(!strcmp(word,"[Triangles,\0")){
      fscanf(file,"%s",word);
      fscanf(file,"%i",&cant);
      readFaces(0,cant,fc);
    }
    if(!strcmp(word,"[Squares,\0")){
      fscanf(file,"%s",word);
      fscanf(file,"%i",&cant);
      readFaces(1,cant,fc);
    }
  }
  return true;
}

void ReadMdl::readFaces(int type, int cant, FaceContainer *fc){
  int n,point;
  vector<int> points;
  Face *newface;
  n=(type==0)?3:4;
  points.reserve(n);

  for(int i=0;i<cant;i++){
    for(int j=0;j<n;j++){
      fscanf(file,"%i",&point);
      points.push_back(point);
    }
    for(int j=0;j<3;j++)
      fscanf(file,"%i",&point);

    newface = new Face(points);
    fc->addFace(newface);
    points.clear();
  }
}

bool ReadMdl::execute(vector<Point> &vpoints, FaceContainer *fc){
	
  file=fopen(name.c_str(),"r");
  if(file==NULL){
    cout << "Error while trying to read: \"";
    cout << name << "\"\n";
    return false;
  }
  if(!points(vpoints)){
    fclose(file);
    return false;
  }

  if(!faces(fc)){
    fclose(file);
    return false;
  }

  fclose(file);
  
  return true;
}
