#include "Hexahedra.h"

Hexahedra::Hexahedra(vector<int> &points, int mat, int idx) : Element(points,mat,idx){

}

Hexahedra::~Hexahedra(){

}

vector<vector <int> > Hexahedra::getTetras(){
  vector<int> points1(4,-1);
  vector<int> points2(4,-1);
  vector<int> points3(4,-1);
  vector<int> points4(4,-1);
  vector<int> points5(4,-1);
  vector<vector <int> > tetras;
  tetras.reserve(5);

  points1[0] = epoint[0];
  points1[1] = epoint[1];
  points1[2] = epoint[2];
  points1[3] = epoint[5];

  points2[0] = epoint[5];
  points2[1] = epoint[7];
  points2[2] = epoint[6];
  points2[3] = epoint[2];

  points3[0] = epoint[0];
  points3[1] = epoint[2];
  points3[2] = epoint[3];
  points3[3] = epoint[7];

  points4[0] = epoint[4];
  points4[1] = epoint[7];
  points4[2] = epoint[5];
  points4[3] = epoint[0];

  points5[0] = epoint[0];
  points5[1] = epoint[2];
  points5[2] = epoint[7];
  points5[3] = epoint[5];

  tetras.push_back(points1);
  tetras.push_back(points2);
  tetras.push_back(points3);
  tetras.push_back(points4);
  tetras.push_back(points5);

  return tetras;
}

vector<int> Hexahedra::getFacePoints(int index){
  vector<int> aux;
  aux.reserve(4);
  switch(index){
    case 0: 
      aux.push_back(epoint[0]);
      aux.push_back(epoint[1]);
      aux.push_back(epoint[2]);
      aux.push_back(epoint[3]);
      break;
    case 1:
      aux.push_back(epoint[3]);
      aux.push_back(epoint[2]);
      aux.push_back(epoint[6]);
      aux.push_back(epoint[7]);
      break;
    case 2:
      aux.push_back(epoint[4]);
      aux.push_back(epoint[7]);
      aux.push_back(epoint[6]);
      aux.push_back(epoint[5]);
      break;
    case 3:
      aux.push_back(epoint[0]);
      aux.push_back(epoint[4]);
      aux.push_back(epoint[5]);
      aux.push_back(epoint[1]);
      break;
    case 4:
      aux.push_back(epoint[1]);
      aux.push_back(epoint[5]);
      aux.push_back(epoint[6]);
      aux.push_back(epoint[2]);
      break;
    case 5:
      aux.push_back(epoint[0]);
      aux.push_back(epoint[3]);
      aux.push_back(epoint[7]);
      aux.push_back(epoint[4]);
      break;
    default:
      break;
  }
  return aux;
}

vector<int> Hexahedra::getEdge(int index){
  vector<int> edge (2,-1);

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
       edge[0]=epoint[4];
       edge[1]=epoint[5];
       break;
     case 5:
       edge[0]=epoint[5];
       edge[1]=epoint[6];
       break;
     case 6:
       edge[0]=epoint[6];
       edge[1]=epoint[7];
       break;
     case 7:
       edge[0]=epoint[7];
       edge[1]=epoint[4];
       break;
     case 8:
       edge[0]=epoint[0];
       edge[1]=epoint[4];
       break;
     case 9:
       edge[0]=epoint[1];
       edge[1]=epoint[5];
       break;
     case 10:
       edge[0]=epoint[2];
       edge[1]=epoint[6];
       break;
     case 11:
       edge[0]=epoint[3];
       edge[1]=epoint[7];
       break;
     default:
       break;
  }
  return edge;
}

vector<int> Hexahedra::getEdges(int index){
  vector<int> nodeedges;
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
      nodeedges.push_back(epoint[5]);
      break;
    case 2:
      nodeedges.push_back(epoint[3]);
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[6]);
      break;
    case 3:
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[7]);
      break;
    case 4:
      nodeedges.push_back(epoint[7]);
      nodeedges.push_back(epoint[5]);
      nodeedges.push_back(epoint[0]);
      break;
    case 5:
      nodeedges.push_back(epoint[4]);
      nodeedges.push_back(epoint[6]);
      nodeedges.push_back(epoint[1]);
      break;
    case 6:
      nodeedges.push_back(epoint[5]);
      nodeedges.push_back(epoint[7]);
      nodeedges.push_back(epoint[2]);
      break;
    case 7:
      nodeedges.push_back(epoint[6]);
      nodeedges.push_back(epoint[4]);
      nodeedges.push_back(epoint[3]);
      break;
    default:
      cerr << "invalid node (" << index << ") at geometry/Hexahedra::getEdges\n";
  }
  return nodeedges;
}

void Hexahedra::getToStandarFormat(FileFormat *ff){
  epoint = ff->formatInputHexahedra(epoint);
}

vector<int> Hexahedra::getPointsInFormat(FileFormat *ff){
  return ff->formatOutputHexahedra(epoint);
}
