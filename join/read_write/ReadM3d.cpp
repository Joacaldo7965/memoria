#include "ReadM3d.h"

ReadM3d::ReadM3d(string name){
	this->name=name;
	bounds.assign(6,-1);
}

ReadM3d::~ReadM3d(){
	
}

bool ReadM3d::points(vector<PointM3d> &vpoints){
	char word [256];
	int cant,i=0,type;
	double x,y,z;
	
	while(1){
		if(!fscanf(file,"%s",word))
			return 0;
		if(!strcmp(word,"ARRAY1<STRING>]\0"))
			break;
	}
	fscanf(file,"%i",&cant);
	vpoints.reserve(cant);
	
	
	if(cant<=0){
		cerr << "warning: no nodes were found\n";
		return true;
	}
	
	//read the first point (to initialize the bounds)
	fscanf(file,"%i",&type);
	fscanf(file,"%s",word);
	x=atof(word);
	fscanf(file,"%s",word);
	y=atof(word);
	fscanf(file,"%s",word);
	z=atof(word);
	PointM3d p (x,y,z,i);
	p.setM3dCode(type);
	if(type == 3 || type == 2){
		Point projection(0,0,0,-1);
		fscanf(file,"%s",word);
		projection[0]=atof(word);
		fscanf(file,"%s",word);
		projection[1]=atof(word);
		fscanf(file,"%s",word);
		projection[2]=atof(word);
		p.setM3dProjection(projection);
	}
	vpoints.push_back(p);
	
	bounds[0]=bounds[3]=x;
	bounds[1]=bounds[4]=y;
	bounds[2]=bounds[5]=z;
	
	for(i=1;i<cant;i++){
		fscanf(file,"%i",&type);
		fscanf(file,"%s",word);
		x=atof(word);
		fscanf(file,"%s",word);
		y=atof(word);
		fscanf(file,"%s",word);
		z=atof(word);
		PointM3d p (x,y,z,i);
		p.setM3dCode(type);
		if(type == 3 || type == 2){
			Point projection(0,0,0,-1);
			fscanf(file,"%s",word);
			projection[0]=atof(word);
			fscanf(file,"%s",word);
			projection[1]=atof(word);
			fscanf(file,"%s",word);
			projection[2]=atof(word);
			p.setM3dProjection(projection);
		}
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

bool ReadM3d::elements(vector<Element *> &velements){
	char word [256];
	int cant,type,idx;
	char etype;
	
	while(1){
		if(!fscanf(file,"%s",word))
			return false;
		if(!strcmp(word,"[Elements,\0"))
			break;
	}
	fscanf(file,"%s",word);
	fscanf(file,"%i",&cant);
	velements.reserve(cant);

	for(int i=0;i<cant;i++){	  
		Element *element;
		fscanf(file,"%s",word);
		if(word[0]=='H'){
			vector<int> points;
			points.reserve(8);
			for(int j=0;j<8;j++){
				fscanf(file,"%i",&idx);
				points.push_back(idx);
			}
			element = new Hexahedra(points,1,i);
		}
		else if(word[0]=='T'){
			vector<int> points;
			points.reserve(4);
			for(int j=0;j<4;j++){
				fscanf(file,"%i",&idx);
				points.push_back(idx);
			}
			element = new Tetrahedra(points,1,i);
		}
		else if(word[0]=='P'){
			vector<int> points;
			points.reserve(5);
			for(int j=0;j<5;j++){
				fscanf(file,"%i",&idx);
				points.push_back(idx);
			}
			element = new Pyramid(points,1,i);
		}
		else if(word[0]=='R'){
			vector<int> points;
			points.reserve(6);
			for(int j=0;j<6;j++){
				fscanf(file,"%i",&idx);
				points.push_back(idx);
			}
			element = new Prism(points,1,i);
		}
		else{
			continue;
		}
		velements.push_back(element);
		for(int i=0;i<3;i++)
			fscanf(file,"%s",word);
	}
	
	return true;
}

bool ReadM3d::execute(vector<PointM3d> &vpoints, vector<Element *> &velements){
	file=fopen(name.c_str(),"r");
	if(file==NULL){
		cout << "Error while trying to read: \"";
		cout << name << "\"\n";
		return false;
	}
	
	cout.flush();
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
