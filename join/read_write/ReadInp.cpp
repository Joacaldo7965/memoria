#include "ReadInp.h"

ReadInp::ReadInp(string name){
	this->name=name;
	bounds.assign(6,-1);
}

ReadInp::~ReadInp(){
	
}

bool ReadInp::header(vector<Point> &vpoints, vector<Element *> &velements){
	//reading any comments
	char word [256];
	while (fscanf(file,"%s",word)!=EOF) {
		if (word[0]=='#') {
			readline();
		}
		else {
			break;
		}
	}
	//reading quantity of nodes and elements.
	vpoints.reserve(atoi(word));
	cout << "points to be readed " << word << endl;
	int cant;
	if (fscanf(file,"%i",&cant)!=EOF) {
		cout << "elements to be readed " << cant << endl;
		velements.reserve(cant);
	}
	else {
		return false;
	}
	readline();
	return true;
}

void ReadInp::readline(){
	char word;
	while (fscanf(file,"%c",&word)!=EOF) {
		if (word=='\n') {
			return;
		}
	}
}

bool ReadInp::points(vector<Point> &vpoints){
	char word [256];
	int cant = vpoints.capacity(),idx;
	double x,y,z;
	
	if (cant<1) {
		return false;
	}
	
	//read the first point (to initialize the bounds)
	fscanf(file,"%i",&idx);
	fscanf(file,"%s",word);
	x=atof(word);
	fscanf(file,"%s",word);
	y=atof(word);
	fscanf(file,"%s",word);
	z=atof(word);
	Point p (x,y,z,idx);
	
	vpoints.push_back(p);
	
	bounds[0]=bounds[3]=x;
	bounds[1]=bounds[4]=y;
	bounds[2]=bounds[5]=z;
	
	for (int i=1; i<cant; i++) {
		fscanf(file,"%i",&idx);
		fscanf(file,"%s",word);
		x=atof(word);
		fscanf(file,"%s",word);
		y=atof(word);
		fscanf(file,"%s",word);
		z=atof(word);
		Point p (x,y,z,idx);
		
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
	return true;
}

bool ReadInp::elements(vector<Element *> &velements){
	char word [256];
	int cant = velements.capacity(), idx, eidx;
	
	for(int i=0; i<cant; i++){	  
		vector<int> points;
		fscanf(file,"%i",&eidx);
		//read  '0' and 'tet' ask if 'hex' also works
		fscanf(file,"%s",word);
		fscanf(file,"%s",word);
		//read nodes
		points.reserve(4);
		for(int j=0;j<4;j++){
			fscanf(file,"%i",&idx);
			points.push_back(idx);
		}
		Element *element = new Tetrahedra(points,1,eidx);
		
		velements.push_back(element);
	}
	return true;
}

bool ReadInp::execute(vector<Point> &vpoints, vector<Element *> &velements){
	file=fopen(name.c_str(),"r");
	if(file==NULL){
		cout << "Error while trying to read: \"";
		cout << name << "\"\n";
		return false;
	}
	
	cout.flush();
	if (!header(vpoints,velements)) {
		fclose(file);
		return false;
	}
	
	if(!points(vpoints)){
		fclose(file);
		return false;
	}
	
	cout.flush();
	if(!elements(velements)){
		fclose(file);
		return false;
	}
	
	fclose(file);
	
	return true;
}
