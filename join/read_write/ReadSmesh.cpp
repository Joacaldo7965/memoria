#include "ReadSmesh.h"

ReadSmesh::ReadSmesh(string nodein, string elemin){
	nodename = nodein;
	elemname = elemin;
	bounds.assign(6,-1);
    offset = 0;
}

ReadSmesh::ReadSmesh(string samename){
	nodename = samename + ".node";
	elemname = samename + ".ele"; 
	bounds.assign(6,-1);
}

ReadSmesh::~ReadSmesh(){
}

bool ReadSmesh::points(vector<Point> &vpoints){
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
	
	//dump
	for(int i=0;i<3;i++){
		fscanf(nodefile,"%s",word);
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
	
	//reading the points
	for(int i=1;i<cant;i++){
		//the index:
		fscanf(nodefile,"%i",&index);
		//the coords;
		fscanf(nodefile,"%s",word);
		x=atof(word);
		fscanf(nodefile,"%s",word);
		y=atof(word);
		fscanf(nodefile,"%s",word);
		z=atof(word);
		Point p(x,y,z,i);
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
	
	cout << "[ReadSmesh] Points readed: " << vpoints.size() << endl;
	
	fclose(nodefile);
	return true;
}


bool ReadSmesh::elements(vector<Element *> &velements){
	int cant,idx;
	vector<int> points;
	points.reserve(3);
	Element *newone;
	FILE *elemfile;
	char word [256];
    int minidx, maxidx = -1;
	
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
	velements.reserve(cant);
    
    minidx = cant+2;
	
	//dump
	for(int i=0;i<2;i++){
		fscanf(elemfile,"%s",word);
    }
	
	for(int i=0;i<cant;i++){
		points.clear();
		fscanf(elemfile,"%s",word);
		for(int j=0;j<4;j++){
			fscanf(elemfile,"%i",&idx);
			points.push_back(idx-offset);
            if (idx<minidx) {
                minidx = idx;
            }
            if (idx>maxidx) {
                maxidx = idx;
            }
		}
		velements.push_back(new Tetrahedra(points,1,i));
	}
    
    cout << "min index: " << minidx << "  max index: " << maxidx << "\n";
    
	return true;
}


vector<int> ReadSmesh::removeRepeated(vector<int> &all){
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

bool ReadSmesh::execute(vector<Point> &vpoints, vector<Element *> &velements){
	
	if(!points(vpoints)){
		cout << " error in node file\n";
		return false;
	}
	
	if(!elements(velements)){
		cout << " error in element file\n";
		return false;
	}
	
	return true;
}

