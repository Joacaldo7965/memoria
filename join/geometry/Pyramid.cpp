#include "Pyramid.h"
#include "Tetrahedra.h"

Pyramid::Pyramid(vector<int> &points, int mat, int idx) : Element(points,mat,idx){
}

Pyramid::~Pyramid(){

}

vector<vector <int> > Pyramid::getTetras(){
  vector<int> points1(4,-1);
  vector<int> points2(4,-1);
  vector<vector <int> > tetras;
  tetras.reserve(2);

  points1[0] = epoint[0];
  points1[1] = epoint[1];
  points1[2] = epoint[2];
  points1[3] = epoint[4];
  
  points2[0] = epoint[0];
  points2[1] = epoint[2];
  points2[2] = epoint[3];
  points2[3] = epoint[4];

  tetras.push_back(points1);
  tetras.push_back(points2);

  return tetras;
}

vector<int> Pyramid::getFacePoints(int index){
  vector<int> aux;
  
  switch(index){ 
    case 0:
      aux.reserve(4);
      aux.push_back(epoint[0]);
      aux.push_back(epoint[1]);
      aux.push_back(epoint[2]);
      aux.push_back(epoint[3]);
      break;
    case 1:
      aux.reserve(3);
      aux.push_back(epoint[1]);
      aux.push_back(epoint[4]);
      aux.push_back(epoint[2]);
      break;
    case 2:
      aux.reserve(3);
      aux.push_back(epoint[2]);
      aux.push_back(epoint[4]);
      aux.push_back(epoint[3]);
      break;
    case 3:
      aux.reserve(3);
      aux.push_back(epoint[3]);
      aux.push_back(epoint[4]);
      aux.push_back(epoint[0]);
      break;
    case 4:
      aux.reserve(3);
      aux.push_back(epoint[0]);
      aux.push_back(epoint[4]);
      aux.push_back(epoint[1]);
      break;
    default:
      break;
  }
  return aux;
}

vector<int> Pyramid::getEdge(int index){
  vector<int> edge(2,-1);
	
  switch(index){
    case 0:
      edge[0]=epoint[0];
      edge[1]=epoint[1];
      break;
    case 1:
      edge[0]=epoint[1];
      edge[1]=epoint[2];
      break;
    case 2:
      edge[0]=epoint[2];
      edge[1]=epoint[3];
      break;
    case 3:
      edge[0]=epoint[3];
      edge[1]=epoint[0];
      break;
    case 4:
      edge[0]=epoint[0];
      edge[1]=epoint[4];
      break;
    case 5:
      edge[0]=epoint[1];
      edge[1]=epoint[4];
      break;
    case 6:
      edge[0]=epoint[2];
      edge[1]=epoint[4];
      break;
    case 7:
      edge[0]=epoint[3];
      edge[1]=epoint[4];
      break;
    default:
      break;
  }
  return edge;
}

vector<int> Pyramid::getEdges(int index){
  vector<int> nodeedges;
  if(index==4)
    nodeedges.reserve(4);
  else
    nodeedges.reserve(3);
  switch(index){
    case 0:
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[3]);
      nodeedges.push_back(epoint[4]);
      break;
    case 1:
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[4]);
      break;
    case 2:
      nodeedges.push_back(epoint[3]);
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[4]);
      break;
    case 3:
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[4]);
      break;
    case 4:
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[3]);
      break;
    default:
      cerr << "invalid node (" << index << ") at geometry/Pyramid::getEdges\n";
  }
  return nodeedges;
}


void Pyramid::getToStandarFormat(FileFormat *ff){
  epoint = ff->formatInputPyramid(epoint);
}

vector<int> Pyramid::getPointsInFormat(FileFormat *ff){
  return ff->formatOutputPyramid(epoint);
}
