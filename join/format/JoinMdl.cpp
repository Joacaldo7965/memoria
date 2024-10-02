#include "JoinMdl.h"

using namespace std;

void emsg(){
	cout << "use: ./joinmdl input1 input2 output\n";
	cout << "output automatically generated with extension mdl\n";
}

void bbox(vector<Point> p){
	double x1,y1,z1,x2,y2,z2,x,y,z;
	if(p.empty())
		return;
	x1 = x2 = p[0][0];
	y1 = y2 = p[0][1];
	z1 = z2 = p[0][2];
	
	for(int i=1;i<p.size();i++){
		x = p[i][0];
		y = p[i][1];
		z = p[i][2];
		if(x1 > x)
			x1 = x;
		if(x2 < x)
			x2 = x;
		
		if(y1 > y)
			y1 = y;
		if(y2 < y)
			y2 = y;
		
		if(z1 > z)
			z1 = z;
		if(z2 < z)
			z2 = z;
	}
	
	double dx = x2 - x1,
	dy = y2 - y1,
	dz = z2 - z1;
	
	if(dx<0)dx=-dx;
	if(dy<0)dy=-dy;
	if(dz<0)dz=-dz;
	
	cout << "x [" << x1 << "," << x2 << "]: " << dx << endl;
	cout << "y [" << y1 << "," << y2 << "]: " << dy << endl;
	cout << "z [" << z1 << "," << z2 << "]: " << dz << endl;
}

void meshToMdl(char** argv){
	
	ReadMdl rmdl1 (argv[1]);
	ReadMdl rmdl2 (argv[2]);
	WriteMdl wmdl (argv[3]);
	
	vector<Point> p1,p2;
	//vector<JoinPoint> jp2;
	FaceContainer *fc1 = new FaceContainer();
	FaceContainer *fc2 = new FaceContainer();
	
	rmdl1.execute(p1,fc1);
	rmdl2.execute(p2,fc2);
	
	int n1=p1.size(),n2 = p2.size();
	p1.reserve(n1+n2);
	//jp2.reserve(n2);
	
	//join the points
	for(int i=0;i<n2;i++)
		p1.push_back(p2[i]); 
	
	//join the faces.
	for(int i=0;i<fc2->length();i++){
		vector<int> fp = fc2->getFace(i)->getPoints();
		for(int j=0;j<fp.size();j++)
			fp[j]+=n1;
		fc1->addFace(new Face(fp));
	}
	
	cout << "> points " << p1.size() << endl;
	cout << "> faces " << fc1->length() << endl;
	
	wmdl.execute(p1,fc1);
	
	delete fc1;
    delete fc2;
	
}

int main(int argc,char** argv){
	
	if(argc==4){
		meshToMdl(argv);
	}
	else {
		emsg();
		return 1;
	}
	
	return 0;
}

