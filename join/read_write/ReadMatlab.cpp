#include "ReadMatlab.h"

ReadMatlab::ReadMatlab(string nodein, string facein){
  nodename = nodein;
  facename = facein;
  bounds.assign(6,-1);
}

ReadMatlab::ReadMatlab(string samename){
  nodename = "Vertex" + samename + ".txt";
  facename = "Face" + samename + ".txt"; 
}

ReadMatlab::~ReadMatlab(){
}

bool ReadMatlab::points(vector<Point> &vpoints){
  char word [256];
  double x,y,z;
  FILE *nodefile;

  list<Point> lpoints;
  list<Point>::iterator iter;
	
  nodefile = fopen(nodename.c_str(),"r");
  
  if(nodefile==NULL){
    cout << "Error while trying to read: \"";
    cout <<  nodename << "\"\n";
    return false;
  }
  
  int idx=0;

  //read the first point (to initialize the bounds)
  if(fscanf(nodefile,"%s",word)==EOF){
    cerr << "warning: no nodes were found\n";
    return true;
  }

  x=atof(word);
  fscanf(nodefile,"%s",word);
  y=atof(word);
  fscanf(nodefile,"%s",word);
  z=atof(word);
  Point p(x,y,z,idx++);
  lpoints.push_back(p);

  bounds.assign(6,-1);
  bounds[0]=bounds[3]=x;
  bounds[1]=bounds[4]=y;
  bounds[2]=bounds[5]=z;
 
  while(true){
    if(fscanf(nodefile,"%s",word)==EOF)
      break;
    x=atof(word);
    fscanf(nodefile,"%s",word);
    y=atof(word);
    fscanf(nodefile,"%s",word);
    z=atof(word);
    Point p(x,y,z,idx++);
    lpoints.push_back(p);
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
  vpoints.clear();
  vpoints.reserve(idx);

  for(iter=lpoints.begin();iter!=lpoints.end();iter++){
    vpoints.push_back(*iter);
  }
  
  cout << "[ReadMatlab] Points readed: " << vpoints.size() << endl;
  
  fclose(nodefile);
  return true;
}


bool ReadMatlab::faces(FaceContainer *fc){
  vector<int> points;
  ifstream facefile(facename.c_str());
  string line;
  
  getline(facefile,line);
  
  while(!facefile.eof()){
    points.clear();
    points.reserve(4);
    
    for(int i=0 ; i<line.size() ; i+=16){
      string p = line.substr(i,16);
      if(p.size()<16)
  	continue;
      double pr = atof(p.c_str());
      int fp = (int)pr;
      points.push_back(fp-1);
      //cout << ">" << p << "< " << "(" << (int)pr << ")\n";
    }
    Face *newone = new Face(points);
    
    fc->addFace(newone);
    line.clear();
    getline(facefile,line);
  }

  cout << "[ReadMatlab] Faces readed: " << fc->length() << endl;
	
  facefile.close();
  return true;
}


bool ReadMatlab::execute(vector<Point> &vpoints, FaceContainer *fc){
      	
  if(!points(vpoints)){
    cout << " error in node file\n";
    return false;
  }

  if(!faces(fc)){
    cout << " error in face file\n";
    return false;
  }
  
  return true;
}

