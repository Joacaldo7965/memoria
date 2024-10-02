#include "ReadPascal.h"

ReadPascal::ReadPascal(string nodein, string elemin){
	nodename = nodein;
	elemname = elemin;
	bounds.assign(6,-1);
    offset = 0;
}

ReadPascal::ReadPascal(string samename){
	nodename = samename + ".node";
	elemname = samename + ".ele"; 
	bounds.assign(6,-1);
}

ReadPascal::~ReadPascal(){
}

bool ReadPascal::points(vector<Point> &vpoints){
	char word [256];
	int cant=0,index,i;
	double x,y,z;
	FILE *nodefile;
	
	nodefile = fopen(nodename.c_str(),"r");
	
	if(nodefile==NULL){
		cout << "Error while trying to read: \"";
		cout <<  nodename << "\"\n";
		return false;
	}
	
	fscanf(nodefile,"%i",&cant);
	vpoints.reserve(cant);
	
	if(cant<=0){
		cerr << "warning: no nodes were found\n";
		return true;
	}
	
	//the index:
	fscanf(nodefile,"%i",&index);
    offset = index;
	//the coords;
	fscanf(nodefile,"%s",word);
	x=atof(word);
	fscanf(nodefile,"%s",word);
	y=atof(word);
	fscanf(nodefile,"%s",word);
	z=atof(word);
	Point p(x,y,z,0);
	vpoints.push_back(p);
	bounds[0]=bounds[3]=x;
	bounds[1]=bounds[4]=y;
	bounds[2]=bounds[5]=z;
	
    int prev_idx = index;
    
	//reading the points
	for(int i=1;i<cant;i++){
		//the index:
		fscanf(nodefile,"%i",&index);
        prev_idx++;
        if (index>prev_idx) {
            unsigned int times = index - prev_idx;
            for (unsigned int j=0; j<times; j++) {
                Point phantom(0,0,0,prev_idx+j);
                vpoints.push_back(phantom);
            }
        }
        
        prev_idx = index;
        
        
		//the coords;
		fscanf(nodefile,"%s",word);
		x=atof(word);
		fscanf(nodefile,"%s",word);
		y=atof(word);
		fscanf(nodefile,"%s",word);
		z=atof(word);
		Point p(x,y,z,index);
		vpoints.push_back(p);
		if(bounds[0]>x)
			bounds[0]=x;
		else if(bounds[3]<x)
			bounds[3]=x;
		if(bounds[1]>y)
			bounds[1]=y;
		else if(bounds[4]<y)
			bounds[4]=y;
		if(bounds[2]>z)
			bounds[2]=z;
		else if(bounds[5]<z)
			bounds[5]=z;
	}
	
	cout << "[ReadPascal] Points readed: " << vpoints.size() << endl;
	
	fclose(nodefile);
	return true;
}


bool ReadPascal::elements(FaceContainer *fc){
	int cant,idx;

	FILE *elemfile;
	char word [256];
	
	elemfile = fopen(elemname.c_str(),"r");
	
	if(elemfile==NULL){
        //try with extension .elem
        elemname += "m";
        
        elemfile = fopen(elemname.c_str(),"r");
        
        if(elemfile==NULL){
            cout << "Error while trying to read: \"";
            cout <<  elemname << "\"\n";
        }
	}
	
	
	fscanf(elemfile,"%i",&cant);
	
	for(int i=0;i<cant;i++){
        vector<int> points;
        points.reserve(3);
        
		for(int j=0;j<3;j++){
			fscanf(elemfile,"%i",&idx);
			points.push_back(idx-offset);
		}
        fc->addFace(new Face(points));
	}
    
	return true;
}


vector<int> ReadPascal::removeRepeated(vector<int> &all){
	vector<int> newpoints;
	list<int> tmp;
	list<int>::iterator iter;
	
	tmp.push_back(all[0]);
	for(int i=1;i<8;i++){
		if(all[i-1]!=all[i])
			tmp.push_back(all[i]);
	}
	
	newpoints.reserve(tmp.size());
	for(iter=tmp.begin();iter!=tmp.end();iter++){
		newpoints.push_back(*iter);
	}
	
	return newpoints;
}

bool ReadPascal::execute(vector<Point> &vpoints, FaceContainer *fc){
	
	if(!points(vpoints)){
		cout << " error in node file\n";
		return false;
	}
	
	if(!elements(fc)){
		cout << " error in element file\n";
		return false;
	}
	
	return true;
}

