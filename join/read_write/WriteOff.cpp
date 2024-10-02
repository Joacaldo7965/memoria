#include "WriteOff.h"

//-------------------------------------------------------------
//-------------------------------------------------------------
WriteOff::WriteOff(string name){
	outname = name;
	outname+=".off\0";
	
}

//-------------------------------------------------------------
//-------------------------------------------------------------
WriteOff::~WriteOff(){

}

//-------------------------------------------------------------
//-------------------------------------------------------------
void WriteOff::writeHead(FILE *f){
	/*fprintf(f,"%s","(geometry main { : foo })\n");
	 fprintf(f,"%s","(read geometry { define foo {\n");
	 fprintf(f,"%s","INST\n");
	 fprintf(f,"%s","geom appearance {\n");
	 fprintf(f,"%s","   +face\n");
	 fprintf(f,"%s","   +edge\n");
	 fprintf(f,"%s","   -vect\n");
	 fprintf(f,"%s","   +concave\n");
	 fprintf(f,"%s","   shading flat\n");
	 fprintf(f,"%s"," }\n");*/
	fprintf(f,"%s","OFF\n");
}

//-------------------------------------------------------------
//-------------------------------------------------------------
void WriteOff::writePoints(FILE *f, vector<Point> &points){
	int n = points.size();
	
	for(int i=0;i<n;i++){
		Point p = points.at(i);
		if(p.getIndex()==-1){
			cout << "invalid index for a point in ";
			cout << "WriteOff: -1\n";
		} 
		fprintf(f,"%f",p[0]);
		fprintf(f," %f",p[1]);
		fprintf(f," %f\n",p[2]);
	}
}

//-------------------------------------------------------------
//-------------------------------------------------------------
void WriteOff::writeFaces(FILE *f, FaceContainer *fc,
						  bool color_option){
	
	fprintf(f,"\n");
	int n = fc->length();
	for(int i=0;i<n;i++){
		Face *face = fc->getFace(i);
		vector<int> fps = face->getPoints();
		fprintf(f,"%i ",(int)fps.size());
		for(int j=0;j<fps.size();j++) 
			fprintf(f,"%i ",fps[j]);
		
		if (color_option) {
			string scolor = face->getColor();
			char color [scolor.size()+1];
			for (int j=0; j<scolor.size(); j++) {
				color[j] = scolor[j];
			}
			color[scolor.size()]='\0';
			fprintf(f,"%s",color);			
		}
		fprintf(f,"\n");
	}
}

//-------------------------------------------------------------
//-------------------------------------------------------------
void WriteOff::writeFaces(FILE *f, 
						  vector<vector<unsigned int> > &faces){
	
	fprintf(f,"\n");
	for (unsigned int i=0; i<faces.size(); i++) {
		
		vector<unsigned int> fps = faces[i];
		fprintf(f,"%i ", (int)fps.size());
		
		for (unsigned int j=0; j<fps.size(); j++) {
			fprintf(f,"%i ",fps[j]);
		}
		fprintf(f,"\n");
	}
	
}

//-------------------------------------------------------------
//-------------------------------------------------------------
void WriteOff::execute(vector<Point> &points,
					   FaceContainer *fc){
	
	FILE *f = fopen(outname.c_str(),"wt");
	
	writeHead(f);
	fprintf(f,"%i %i %i\n\n",(int)points.size(),fc->length(),0);
	writePoints(f,points);
	writeFaces(f,fc,true);
	
	fclose(f);
}

//-------------------------------------------------------------
//-------------------------------------------------------------
void WriteOff::execute(vector<Point> &points, 
					   FaceContainer *fc,
					   bool color_option){
	
	FILE *f = fopen(outname.c_str(),"wt");
	
	writeHead(f);
	fprintf(f,"%i %i %i\n\n",(int)points.size(),fc->length(),0);
	writePoints(f,points);
	writeFaces(f,fc,color_option);
	
	fclose(f);
}

//-------------------------------------------------------------
//-------------------------------------------------------------
void WriteOff::execute(vector<Point> &points, 
					   vector<vector<unsigned int> > &faces){
	
	FILE *f = fopen(outname.c_str(),"wt");
	
	writeHead(f);
	fprintf(f,"%i %i %i\n\n",(int)points.size(),(int)faces.size(),0);
	writePoints(f,points);
	writeFaces(f,faces);
	
	fclose(f);
}