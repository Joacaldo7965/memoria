#include "M3dToMdlCloud.h"

using namespace std;

void emsg(){
  cout << "use: ./mesh2mdl input output\n";
  cout << "output automatically generated with extension mdl\n";
}

void bbox(vector<Point> p){
  double x1,y1,z1,x2,y2,z2,x,y,z;
  if(p.empty())
    return;
  x1 = x2 = p[0][0];
  y1 = y2 = p[0][1];
  z1 = z2 = p[0][2];

  for(int i=1;i<p.size();i++){
    x = p[i][0];
    y = p[i][1];
    z = p[i][2];
    if(x1 > x)
      x1 = x;
    if(x2 < x)
      x2 = x;

    if(y1 > y)
      y1 = y;
    if(y2 < y)
      y2 = y;

    if(z1 > z)
      z1 = z;
    if(z2 < z)
      z2 = z;
  }

  double dx = x2 - x1,
	 dy = y2 - y1,
	 dz = z2 - z1;
  
  if(dx<0)dx=-dx;
  if(dy<0)dy=-dy;
  if(dz<0)dz=-dz;
  
  cout << "x [" << x1 << "," << x2 << "]: " << dx << endl;
  cout << "y [" << y1 << "," << y2 << "]: " << dy << endl;
  cout << "z [" << z1 << "," << z2 << "]: " << dz << endl;
}

void meshToMdl(char** argv){
  
  ReadM3d rm (argv[1]);
  WriteMdl wmd(argv[2]);
  
  vector<Point> points;
  vector<PointM3d> m3dp;
  vector<Element *> elements;
  FaceContainer *fc = new FaceContainer();
  
  rm.execute(m3dp,elements);
  points.reserve(m3dp.size());
  for(int i=0;i<m3dp.size();i++)
    points.push_back(Point (m3dp[i][0],
			    m3dp[i][1],
			    m3dp[i][2],
			    m3dp[i].getIndex()));

  bbox(points);
  
  for(int i=0;i<elements.size();i++){
    int enf = elements[i]->numberOfFaces();
    for(int j=0;j<enf;j++){
      vector<int> nodes = elements[i]->getFacePoints(j);
      Face *f = new Face(nodes);
      fc->addFace(f);
    }	      
  }
  
  //wmd.writeOnlyPoints(points);
  wmd.writeWithTriangleFaces(points,fc);

  for(int i=0;i<elements.size();i++)
    delete elements[i];
  
}

int main(int argc,char** argv){

  if(argc==3){
    meshToMdl(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

