#include "MeshToM3d.h"

using namespace std;

void emsg(){
  cout << "use: ./mesh2m3d input output\n";
  cout << "output automatically generated with extension m3d\n";
}

vector<PointM3d> getM3dPoints(vector<Point> &ansyspoints){
  vector<PointM3d> pointsm3d;
  int n = ansyspoints.size();
  pointsm3d.reserve(n);
  for(int i=0;i<n;i++){
    pointsm3d.push_back(PointM3d (ansyspoints[i][0],
                                  ansyspoints[i][1],
                                  ansyspoints[i][2],
                                  ansyspoints[i].getIndex()));
  }
  return pointsm3d;
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

void meshToM3d(char** argv){
  
  ReadMeshVolume rmv (argv[1]);
  WriteM3d wmd(argv[2]);
  
  vector<Point> points;
  vector<PointM3d> m3dpoints;
  vector<Element *> elements;
  
  rmv.execute(points,elements);

  m3dpoints = getM3dPoints(points);
  
  wmd.execute(m3dpoints,elements);

  cout << "> points " << points.size() << endl;
  cout << "> elements " << elements.size() << endl;

  //bbox(points);

  for(int i=0;i<elements.size();i++)
    delete elements[i];
  
}

int main(int argc,char** argv){

  if(argc==3){
    meshToM3d(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

