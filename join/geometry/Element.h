#ifndef Element_h
#define Element_h 1

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "../read_write/FileFormat.h"
#include "Point.h"
#include <string>

using namespace std;

class Element{
    
public:
    Element(vector<int> &points, int mat, int idx);
    
    Element(vector<int> &points, int idx);
    
    Element(vector<int> &points);
    
    virtual ~Element();
    
    virtual int getIndex();
    
    virtual int getMaterial();
    
    virtual void setIndex(int idx);
    
    virtual void setMaterial(int mat);
    
    virtual int numberOfPoints();
    
    virtual int numberOfFaces()=0;
    
    virtual int numberOfEdges()=0;
    
    virtual void updatePoint(int oldp, int newp);
    
    virtual int getPoint(int pos);
    
    virtual vector<int> &getPoints();
    
    virtual bool hasPoint(int index);
    
    virtual void setColor(string newcolor);
    
    virtual string getColor();
    
    virtual char getCharType()=0;
    
    virtual vector<int> getFacePoints(int index)=0;
    
    //returns the two nodes in edge index
    virtual vector<int> getEdge(int index)=0;
    
    //returns a list with nodes connected to index
    virtual vector<int> getEdges(int index)=0;
    
    //The two following methods will allow to pass from any
    //possible format of IOFile to the standar M3d used in
    //geomtry convention
    virtual void getToStandarFormat(FileFormat *ff)=0;
    
    virtual vector<int> getPointsInFormat(FileFormat *ff)=0;
    
    virtual double getVolume(vector<Point> &points);
    
    virtual vector<vector <int> > getTetras()=0;
    
    virtual void updatePoints(vector<int> tmp);
    
    virtual unsigned int getAnsysAuxType()=0;
    
protected:
    
    string color;
    vector<int> epoint;
    int index,material;
    
};

inline void Element::setIndex(int idx){
    index=idx;
}

inline void Element::setMaterial(int mat){
    material=mat;
}

inline void Element::updatePoints(vector<int> tmp){
    for(int i=0;i<tmp.size();i++)
        epoint[i]=tmp[i];
}

inline vector<int> &Element::getPoints(){
    return epoint;
}

inline void Element::setColor(string newcolor){
    color = newcolor;
}

inline string Element::getColor() {
    return color;
}

inline int Element::numberOfPoints(){
    return epoint.size();
}

inline int Element::getPoint(int pos){
    return epoint.at(pos);
}

inline int Element::getIndex(){
    return index;
}

inline int Element::getMaterial(){
    return material;
}

inline bool Element::hasPoint(int index){
    for(int i=0;i<epoint.size();i++){
        if(epoint[i]==index)
            return true;
    }
    return false;
}

ostream& operator<<(ostream& o,Element &e);

bool operator==(Element &e1, Element &e2);

#endif
