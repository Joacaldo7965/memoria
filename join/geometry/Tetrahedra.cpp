#include "Tetrahedra.h"

Tetrahedra::Tetrahedra(vector<int> &points, int mat, int idx) : Element(points,mat,idx){
}

Tetrahedra::~Tetrahedra(){

}

vector<vector <int> > Tetrahedra::getTetras(){
  vector<vector <int> > tetras;
  tetras.reserve(1);

  tetras.push_back(epoint);

  return tetras;
}

vector<int> Tetrahedra::getFacePoints(int index){
  vector<int> aux;
  aux.reserve(3);
  
  switch(index){
    case 0:
      aux.push_back(epoint[0]);
      aux.push_back(epoint[1]);
      aux.push_back(epoint[2]);
      break;
    case 1:
      aux.push_back(epoint[1]);
      aux.push_back(epoint[3]);
      aux.push_back(epoint[2]);
      break;
    case 2:
      aux.push_back(epoint[1]);
      aux.push_back(epoint[0]);
      aux.push_back(epoint[3]);
      break;
    case 3:
      aux.push_back(epoint[0]);
      aux.push_back(epoint[2]);
      aux.push_back(epoint[3]);
      break;
    default:
      cout << "asking for an invalid Tetrahedra Face\n";
      break;
  }
  return aux;
}

vector<int> Tetrahedra::getEdge(int index){
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
      edge[1]=epoint[0];
      break;
    case 3:
      edge[0]=epoint[0];
      edge[1]=epoint[3];
      break;
    case 4:
      edge[0]=epoint[1];
      edge[1]=epoint[3];
      break;
    case 5:
      edge[0]=epoint[2];
      edge[1]=epoint[3];
      break;
    default:
      break;
  }
  return edge;
}

vector<int> Tetrahedra::getEdges(int index){
  vector<int> nodeedges;
  nodeedges.reserve(3);
  switch(index){
    case 0:
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[3]);
      break;
    case 1:
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[3]);
      break;
    case 2:
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[3]);
      nodeedges.push_back(epoint[1]);
      break;
    case 3:
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[2]);
      break;
    default:
      cerr << "invalid node (" << index << ") at geometry/Tetrahedra::getEdges\n";
  }
  return nodeedges;
}

void Tetrahedra::getToStandarFormat(FileFormat *ff){
  epoint = ff->formatInputTetrahedra(epoint);
}

vector<int> Tetrahedra::getPointsInFormat(FileFormat *ff){
  return ff->formatOutputTetrahedra(epoint);
}
