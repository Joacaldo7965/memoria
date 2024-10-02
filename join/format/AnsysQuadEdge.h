#ifndef AnsysQuadEdge_h
#define AnsysQuadEdge_h 1

#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::ostream;
using std::cout;

class AnsysQuadEdge{
	
public:
	AnsysQuadEdge();
	
	AnsysQuadEdge(const unsigned int &idx1, const unsigned int &idx2);
	
	virtual ~AnsysQuadEdge();
	
	virtual void assign(const unsigned int &idx1, const unsigned int &idx2);
	
	virtual void updateMidPoint(const unsigned int &idx);
	
	virtual void setMidPoint(unsigned int &mid);
	
	virtual unsigned int operator[](unsigned const int &pos) const;
	
	virtual void operator=(const AnsysQuadEdge &e);
	
	friend ostream& operator<<(ostream& o, const AnsysQuadEdge &e);
	
	friend bool operator==(const AnsysQuadEdge &e1, const AnsysQuadEdge &e2);
	
	friend bool operator!=(const AnsysQuadEdge &e1, const AnsysQuadEdge &e2);
	
	friend bool operator<(const AnsysQuadEdge &e1, const AnsysQuadEdge &e2);
	
	
protected:
	
	vector<unsigned int> info;
};

inline void AnsysQuadEdge::updateMidPoint(const unsigned int &idx){
	info[2] = idx;
}

inline unsigned int AnsysQuadEdge::operator[](unsigned const int &pos) const{
	return info.at(pos);
}

inline void AnsysQuadEdge::setMidPoint(unsigned int &mid){
	info[2] = mid;
}

#endif
