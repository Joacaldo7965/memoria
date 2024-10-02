#include "AnsysFormat.h"

AnsysFormat::AnsysFormat(){

}

AnsysFormat::~AnsysFormat(){

}

vector<int> AnsysFormat::formatInputHexahedra(vector<int> &epoint){
  vector<int> aux (8,-1);
  aux[0] = epoint[7]-1;
  aux[1] = epoint[4]-1;
  aux[2] = epoint[5]-1;
  aux[3] = epoint[6]-1;
  aux[4] = epoint[3]-1;
  aux[5] = epoint[0]-1;
  aux[6] = epoint[1]-1;
  aux[7] = epoint[2]-1;
  return aux;
}

vector<int> AnsysFormat::formatInputPrism(vector<int> &epoint){
  vector<int> aux (6,-1);
  for(int i=0;i<6;i++)
    aux[i] = epoint[i]-1;
  return aux;
}

vector<int> AnsysFormat::formatInputPyramid(vector<int> &epoint){
  vector<int> aux (5,-1);
  for(int i=0;i<5;i++)
    aux[i] = epoint[i]-1;
  return aux;
}

vector<int> AnsysFormat::formatInputTetrahedra(vector<int> &epoint){
  vector<int> aux (4,-1);
  for(int i=0;i<4;i++)
    aux[i] = epoint[i]-1;
  return aux;
}

vector<int> AnsysFormat::formatOutputHexahedra(vector<int> &epoint){
  vector<int> aux (8,-1);
  aux[0] = epoint[5]+1;
  aux[1] = epoint[6]+1;
  aux[2] = epoint[7]+1;
  aux[3] = epoint[4]+1;
  aux[4] = epoint[1]+1;
  aux[5] = epoint[2]+1;
  aux[6] = epoint[3]+1;
  aux[7] = epoint[0]+1;
  return aux;	
}

vector<int> AnsysFormat::formatOutputPrism(vector<int> &epoint){
  vector<int> aux (8,-1);
  aux[0] = epoint[0]+1;
  aux[1] = epoint[1]+1;
  aux[2] = epoint[2]+1;
  aux[3] = epoint[2]+1;
  aux[4] = epoint[3]+1;
  aux[5] = epoint[4]+1;
  aux[6] = epoint[5]+1;
  aux[7] = epoint[5]+1; 
  return aux;
}

vector<int> AnsysFormat::formatOutputPyramid(vector<int> &epoint){
  vector<int> aux (8,-1);
  aux[0] = epoint[0]+1;
  aux[1] = epoint[1]+1;
  aux[2] = epoint[2]+1;
  aux[3] = epoint[3]+1;
  aux[4] = epoint[4]+1;
  aux[5] = epoint[4]+1;
  aux[6] = epoint[4]+1;
  aux[7] = epoint[4]+1;
  return aux;
}

vector<int> AnsysFormat::formatOutputTetrahedra(vector<int> &epoint){
  vector<int> aux (8,-1);
    /*
  aux[0] = epoint[0]+1;
  aux[1] = epoint[1]+1;
  aux[2] = epoint[2]+1;
  aux[3] = epoint[2]+1;
  aux[4] = epoint[3]+1;
  aux[5] = epoint[3]+1;
  aux[6] = epoint[3]+1;
  aux[7] = epoint[3]+1;*/
    aux[0] = epoint[0]+1;
    aux[1] = epoint[1]+1;
    aux[2] = epoint[2]+1;
    aux[3] = epoint[3]+1;
    for (unsigned int i=4;i<8 ; i++) {
        aux[i] = 0;
    }

  return aux;
}
