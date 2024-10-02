#include "Prism.h"

Prism::Prism(vector<int> &points, int mat, int idx) : Element(points,mat,idx){

}

Prism::~Prism(){

}

vector<vector <int> > Prism::getTetras(){
  vector<int> t1,t2,t3;
  vector<vector <int> > tetras;
  t1.reserve(4);
  t2.reserve(4);
  t3.reserve(4);

  tetras.reserve(3);

  t1.push_back(epoint[0]);
  t1.push_back(epoint[4]);
  t1.push_back(epoint[5]);
  t1.push_back(epoint[3]);

  t2.push_back(epoint[2]);
  t2.push_back(epoint[4]);
  t2.push_back(epoint[5]);
  t2.push_back(epoint[0]);

  t3.push_back(epoint[1]);
  t3.push_back(epoint[4]);
  t3.push_back(epoint[2]);
  t3.push_back(epoint[0]);

  tetras.push_back(t1);
  tetras.push_back(t2);
  tetras.push_back(t3);
  
  return tetras;
}

vector<int> Prism::getFacePoints(int index){
  vector<int> aux;
  
  switch(index){ 
    case 0:
      aux.reserve(4);
      aux.push_back(epoint[0]);
      aux.push_back(epoint[3]);
      aux.push_back(epoint[4]);
      aux.push_back(epoint[1]);
      break;
    case 1:
      aux.reserve(4);
      aux.push_back(epoint[1]);
      aux.push_back(epoint[4]);
      aux.push_back(epoint[5]);
      aux.push_back(epoint[2]);
      break;
    case 2:
      aux.reserve(4);
      aux.push_back(epoint[0]);
      aux.push_back(epoint[2]);
      aux.push_back(epoint[5]);
      aux.push_back(epoint[3]);
      break;
    case 3:
      aux.reserve(3);
      aux.push_back(epoint[0]);
      aux.push_back(epoint[1]);
      aux.push_back(epoint[2]);
      break;
    case 4:
      aux.reserve(3);
      aux.push_back(epoint[3]);
      aux.push_back(epoint[5]);
      aux.push_back(epoint[4]);
      break;
    default:
      break;
  }
  return aux;
}

vector<int> Prism::getEdge(int index){
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
      edge[0]=epoint[3];
      edge[1]=epoint[4];
      break;
    case 4:
      edge[0]=epoint[4];
      edge[1]=epoint[5];
      break;
    case 5:
      edge[0]=epoint[5];
      edge[1]=epoint[3];
      break;
    case 6:
      edge[0]=epoint[0];
      edge[1]=epoint[3];
      break;
    case 7:
      edge[0]=epoint[1];
      edge[1]=epoint[4];
      break;
    case 8:
      edge[0]=epoint[2];
      edge[1]=epoint[5];
      break;
    default:
      break;
  }
  return edge;
}

vector<int> Prism::getEdges(int index){
  vector<int> nodeedges;
  nodeedges.reserve(3);
  switch(index){
    case 0:
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[3]);
      break;
    case 1:
      nodeedges.push_back(epoint[2]);
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[4]);
      break;
    case 2:
      nodeedges.push_back(epoint[0]);
      nodeedges.push_back(epoint[1]);
      nodeedges.push_back(epoint[5]);
      break;
    case 3:
      nodeedges.push_back(epoint[5]);
      nodeedges.push_back(epoint[4]);
      nodeedges.push_back(epoint[0]);
      break;
    case 4:
      nodeedges.push_back(epoint[3]);
      nodeedges.push_back(epoint[5]);
      nodeedges.push_back(epoint[1]);
      break;
    case 5:
      nodeedges.push_back(epoint[4]);
      nodeedges.push_back(epoint[3]);
      nodeedges.push_back(epoint[2]);
      break;
    default:
      cerr << "invalid node (" << index << ") at geometry/Prism::getEdges\n";
  }
  return nodeedges;
}

void Prism::getToStandarFormat(FileFormat *ff){
  epoint = ff->formatInputPrism(epoint);
}

vector<int> Prism::getPointsInFormat(FileFormat *ff){
  return ff->formatOutputPrism(epoint);
}
