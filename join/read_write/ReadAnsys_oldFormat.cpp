#include "ReadAnsys.h"

ReadAnsys::ReadAnsys(string nodein, string elemin){
	nodename = nodein;
	elemname = elemin;
	bounds.assign(6,-1);
}

ReadAnsys::ReadAnsys(string samename){
	nodename = samename + ".node";
	elemname = samename + ".elem";
	bounds.assign(6,-1);
}

ReadAnsys::~ReadAnsys(){
}

bool ReadAnsys::points(vector<Point> &vpoints){
	char word [256];
	int cant=0,index,i;
	double x,y,z;
	FILE *nodefile;
	
	list<Point> lpoints;
	list<Point>::iterator iter;
	
	nodefile = fopen(nodename.c_str(),"r");
	
	if(nodefile==NULL){
		cout << "Error while trying to read: \"";
		cout <<  nodename << "\"\n";
		return false;
	}
	
	//read the first point (to initialize the bounds)
	if(fscanf(nodefile,"%i",&index)==EOF){
		cerr << "warning: no nodes were found\n";
		return true;
	}
	fscanf(nodefile,"%s",word);
	x=atof(word);
	fscanf(nodefile,"%s",word);
	y=atof(word);
	fscanf(nodefile,"%s",word);
	z=atof(word);
	Point p(x,y,z,index-1);
	lpoints.push_back(p);
	cant++;
	bounds[0]=bounds[3]=x;
	bounds[1]=bounds[4]=y;
	bounds[2]=bounds[5]=z;
	
	while(true){
		if(fscanf(nodefile,"%i",&index)==EOF)
			break;
		fscanf(nodefile,"%s",word);
		x=atof(word);
		fscanf(nodefile,"%s",word);
		y=atof(word);
		fscanf(nodefile,"%s",word);
		z=atof(word);
		Point p(x,y,z,index-1);
		lpoints.push_back(p);
		cant++;
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
	vpoints.clear();
	vpoints.reserve(cant);
	
	for(i=0, iter=lpoints.begin();iter!=lpoints.end();iter++,i++){
		vpoints.push_back(*iter);
	}
	
	cout << "[ReadAnsys] Points readed: " << vpoints.size() << endl;
	
	fclose(nodefile);
	return true;
}


bool ReadAnsys::elements(vector<Element *> &velements){
	vector<int> all,points;
	list<Element *> lelements;
	list<Element *>::iterator iter;
	ifstream elemfile(elemname.c_str());
	string line;
	Element *newone;
	FileFormat *ansysformat = new AnsysFormat();
	
	all.reserve(14);
	getline(elemfile,line);
	
	while(!elemfile.eof()){
		all.clear();
		points.clear();
		
		for(int i=0 ; i<line.size() ; i+=6){
			all.push_back(atoi((line.substr(i,6)).c_str()));
		}
		
		points = removeRepeated(all);
		
		switch(points.size()){
			case 8:
				newone = new Hexahedra(points, all[8],all[13]-1);
				break;
			case 6:
				newone = new Prism(points,all[8],all[13]-1);
				break;
			case 5:
				newone = new Pyramid(points,all[8],all[13]-1);
				break;
			case 4:
				newone = new Tetrahedra(points,all[8],all[13]-1);
				break;
			default:
				cout << "[ReadAnsys] invalid element. NPoints: " << points.size() << endl;
				break;
		}
		
		newone->getToStandarFormat(ansysformat);
		lelements.push_back(newone);
		line.clear();
		getline(elemfile,line);
	}
	
	velements.reserve(lelements.size());
	
	for(iter=lelements.begin();iter!=lelements.end();iter++){
		velements.push_back(*iter);
	}
	
	cout << "[ReadAnsys] Elements readed: " << velements.size() << endl;
	
	elemfile.close();
	return true;
}


vector<int> ReadAnsys::removeRepeated(vector<int> &all){
	vector<int> newpoints;
	list<int> tmp;
	list<int>::iterator iter;
	
   	tmp.push_back(all[0]);
    /*if (all[8]==1) {
        
        //this is a new tetrahedron
        for(int i=1;i<4;i++){
            tmp.push_back(all[i]);
        }
    }
    else {*/
        for(int i=1;i<8;i++){
            if(all[i-1]!=all[i])
                tmp.push_back(all[i]);
        }
    //}
	
	newpoints.reserve(tmp.size());
	for(iter=tmp.begin();iter!=tmp.end();iter++){
		newpoints.push_back(*iter);
	}
	
	return newpoints;
}

bool ReadAnsys::execute(vector<Point> &vpoints, vector<Element *> &velements){
	
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

/*vector<PointM3d> ReadAnsys::getM3dPoints(vector<Point> &ansyspoints){
 vector<PointM3d> pointsm3d;
 int n = ansyspoints.size();
 pointsm3d.reserve(n);
 for(int i=0;i<n;i++){
 pointsm3d.push_back(PointM3d (ansyspoints[i][0],
 ansyspoints[i][1],
 ansyspoints[i][2],
 ansyspoints[i].getIndex()));
 }
 }*/

