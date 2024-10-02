#include "Element.h"

Element::Element(vector<int> &points, int mat, int idx){
    index = idx;
    material = mat;
    
    epoint.reserve(points.size());
    for(int i=0;i<points.size();i++)
        epoint.push_back(points[i]);
    
    color = " 1 1 1 ";
}

Element::Element(vector<int> &points, int idx){
    index = idx;
    material = 1;
    
    epoint.reserve(points.size());
    for(int i=0;i<points.size();i++)
        epoint.push_back(points[i]);
    color = " 1 1 1 ";
}

Element::Element(vector<int> &points){
    index = -1;
    material = 1;
    
    epoint.reserve(points.size());
    for(int i=0;i<points.size();i++)
        epoint.push_back(points[i]);
    color = " 1 1 1 ";
}

Element::~Element(){
    
}

double Element:: getVolume(vector<Point> &points){
    vector<vector <int> > tetras = getTetras();
    double volume = 0;
    
    for(int i=0;i<tetras.size();i++){
        vector<int> onetetra = tetras[i];
        Point p1 = points[onetetra[0]],
        p2 = points[onetetra[1]],
        p3 = points[onetetra[2]],
        p4 = points[onetetra[3]];
        Point a = p2-p1, b = p3-p1, c = p4-p1;
        double localvol = a.dot(b.cross(c));
        localvol /=6;
        if(localvol<0)
            localvol*=-1;
        volume += localvol;
    }
    return volume;
}

void Element::updatePoint(int oldp, int newp){
    for(int i=0;i<epoint.size();i++){
        if(oldp == epoint[i]){
            epoint[i] = newp;
        }
    }
}

ostream& operator<<(ostream& o,Element &e){
    o << e.getCharType() << " ";
    for(int i=0;i<e.numberOfPoints();i++)
        o << e.getPoint(i) << " ";
    o << " idx " << e.getIndex();
    return o;
}

bool operator==(Element &e1, Element &e2){
    vector<int> ve1 = e1.getPoints();
    vector<int> ve2 = e2.getPoints();
    bool found;
    if(ve1.size()!=ve2.size())
        return false;
    for(int i=0;i<ve1.size();i++){
        found = false;
        for(int j=0;j<ve2.size();j++){
            if(ve1[i]==ve2[j]){
                found = true;
                break;
            }
        }
        if(!found)
            return false;
    }
    return true;
}
