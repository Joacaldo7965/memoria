#include "AnsysToM3d.h"

using namespace std;

void emsg(){
    cout << "use: ./ansys2m3d input output\n";
    cout << "output will be wrigthen with extensions: node & elem\n";
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

void ansysToM3d(char** argv){
    
    ReadAnsys *ra;
    WriteM3d *wm;
    
    vector<Point> ansyspoints;
    vector<PointM3d> m3dpoints;
    vector<Element *> elements;
    
    ra = new ReadAnsys(argv[1]);
    ra->execute(ansyspoints,elements);
    delete ra;
    
    m3dpoints = getM3dPoints(ansyspoints);
    
    wm = new WriteM3d(argv[2]);
    wm->execute(m3dpoints,elements);
    delete wm;
    
    for(int i=0;i<elements.size();i++)
        delete elements[i];
}

int main(int argc,char** argv){
    
    if(argc==3){
        ansysToM3d(argv);
    }
    else {
        emsg();
        return 1;
    }
    
    return 0;
}

