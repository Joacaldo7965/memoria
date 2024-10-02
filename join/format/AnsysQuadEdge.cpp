#include "AnsysQuadEdge.h"


AnsysQuadEdge::AnsysQuadEdge(){
	info.assign(3,0);
}

AnsysQuadEdge::AnsysQuadEdge(const unsigned int &point1, const unsigned int &point2){
	info.assign(3,0);
	if (point1<point2) {
		info[0]=point1;
		info[1]=point2;
	}
	else {
		info[1]=point1;
		info[0]=point2;
	}
	
	info[2]=0;
}

AnsysQuadEdge::~AnsysQuadEdge(){
	
}

void AnsysQuadEdge::assign(const unsigned int &point1, const unsigned int &point2){
	if (point1<point2) {
		info[0]=point1;
		info[1]=point2;
	}
	else {
		info[1]=point1;
		info[0]=point2;
	}
}


ostream& operator<<(ostream& o, const AnsysQuadEdge &e){
	o << e[0] << " ";
	o << e[1] << " ";
	o << e[2];
	return o;
}

bool operator==(const AnsysQuadEdge &e1, const AnsysQuadEdge &e2) {
	//this possible as AnsysQuadEdges are sorted by min index
	if (e1[0]==e2[0] && e1[1]==e2[1])
		return true;
	return false;
}

bool operator!=(const AnsysQuadEdge &e1, const AnsysQuadEdge &e2) {
	return !(e1==e2);
}

bool operator<(const AnsysQuadEdge &e1, const AnsysQuadEdge &e2) {
	if (e1[0]!=e2[0]){
		return e1[0]<e2[0];
	}
	return e1[1] < e2[1];
}

void AnsysQuadEdge::operator=(const AnsysQuadEdge &e){
	info[0]=e[0];
	info[1]=e[1];
	info[2]=e[2];
}