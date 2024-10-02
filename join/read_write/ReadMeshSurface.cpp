#include "ReadMeshSurface.h"

ReadMeshSurface::ReadMeshSurface(string name){
  this->name=name;
  bounds.assign(6,-1);
}

ReadMeshSurface::~ReadMeshSurface(){

}

bool ReadMeshSurface::points(vector<Point> &vpoints){
  char word [256];
  int cant,i,type;
  double x,y,z;
  
  while(1){
    if(!fscanf(file,"%s",word))
      return 0;
    if(!strcmp(word,"Vertices\0"))
      break;
  }
  fscanf(file,"%i",&cant);
  vpoints.reserve(cant);

  if(cant<=0){
    cerr << "warning: no nodes were found\n";
    return true;
  }

  //read the first point (to initialize the bounds)
  fscanf(file,"%s",word);
  x=atof(word);
  fscanf(file,"%s",word);
  y=atof(word);
  fscanf(file,"%s",word);
  z=atof(word);
  Point p (x,y,z,0);
  vpoints.push_back(p);
  //dump
  fscanf(file,"%s",word);
  bounds[0]=bounds[3]=x;
  bounds[1]=bounds[4]=y;
  bounds[2]=bounds[5]=z;
  
  for(i=1;i<cant;i++){
    fscanf(file,"%s",word);
    x=atof(word);
    fscanf(file,"%s",word);
    y=atof(word);
    fscanf(file,"%s",word);
    z=atof(word);
    Point p (x,y,z,i);
    vpoints.push_back(p);
    //dump
    fscanf(file,"%s",word);
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

bool ReadMeshSurface::faces(FaceContainer *fc){
  char word [256];
  int cant,point;
  vector<int> points;
  Face *newface;
  points.reserve(3);
  bool startincero = false;
  
  while(1){
    if(fscanf(file,"%s",word) == EOF)
      return false;
  
    if(!strcmp(word,"Triangles\0")){
      break;
    }
  }
  fscanf(file,"%i",&cant);

  for(int i=0;i<cant;i++){
    for(int j=0;j<3;j++){
      fscanf(file,"%i",&point);
      //the mesh format starts with node 1 and
      //the mdl with 0 => the node must be reduced:
      point--;
      points.push_back(point);
    }
    //dump
    fscanf(file,"%i",&point);

    newface = new Face(points);
    fc->addFace(newface);
    points.clear();
  }
  return true;
}

bool ReadMeshSurface::execute(vector<Point> &vpoints, FaceContainer *fc){
	
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
