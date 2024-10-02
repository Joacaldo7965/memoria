#include "InpToM3d.h"

using namespace std;

void emsg(){
	cout << "use: ./Inp2m3d input output\n";
	cout << "output will be written with extension m3d\n";
}

vector<PointM3d> getM3dPoints(vector<Point> &inppoints){
	vector<PointM3d> pointsm3d;
	int n = inppoints.size();
	pointsm3d.reserve(n);
	for(int i=0; i<n; i++){
		pointsm3d.push_back(PointM3d (inppoints[i][0],
									  inppoints[i][1],
									  inppoints[i][2],
									  inppoints[i].getIndex()));
	}
	return pointsm3d;
}

void InpToM3d(char** argv){
	
	ReadInp *ri;
	WriteM3d *wm;
	
	vector<Point> inppoints;
	vector<PointM3d> m3dpoints;
	vector<Element *> elements;
	
	ri = new ReadInp(argv[1]);
	ri->execute(inppoints,elements);
	delete ri;
	
	cout << "file readed\n";
	cout.flush();
	
	m3dpoints = getM3dPoints(inppoints);
	
	wm = new WriteM3d(argv[2]);
	wm->execute(m3dpoints,elements);
	delete wm;
	
	for(int i=0;i<elements.size();i++)
		delete elements[i];
}

int main(int argc,char** argv){
	
	if(argc==3){
		InpToM3d(argv);
	}
	else {
		emsg();
		return 1;
	}
	
	return 0;
}

