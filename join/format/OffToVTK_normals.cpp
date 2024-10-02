#include "OffToOff_nc.h"

using namespace std;

void emsg(){
	cout << "use: ./off2vtk_normal input output\n";
	cout << "output automatically generated with extension vtk\n";
}

void offToMdl(char** argv){
	
	ReadOff ro;
	vector<Point> points;
	FaceContainer *fc = new FaceContainer();
	ro.execute(argv[1],points,fc);
	
    string output = argv[2];
    output+=".vtk";

    FILE *f = fopen(output.c_str(),"wt");
    
    fprintf(f,"# vtk DataFile Version 2.0\nUnstructured Grid %s\nASCII",argv[2]);
    fprintf(f,"\n\nDATASET UNSTRUCTURED_GRID\nPOINTS %i float",(int)points.size());

    //write points
    for(unsigned int i=0;i<points.size();i++){
        if (i%2==0) {
            fprintf(f,"\n");
        }
        fprintf(f," %+1.8E",points[i][0]);
        fprintf(f," %+1.8E",points[i][1]);
        fprintf(f," %+1.8E",points[i][2]);
    }
    
    unsigned int connectivity=0;
    for (int i=0; i<fc->length(); i++) {
        connectivity+=fc->getFace(i)->getPoints().size()+1;
    }
    
    fprintf(f,"\n\nCELLS %i %i\n",fc->length(),connectivity);
    
    for (int i=0; i<fc->length(); i++) {
        vector<int> fpts = fc->getFace(i)->getPoints();
        fprintf(f,"\n%lu",fpts.size());
        for (unsigned int j=0; j<fpts.size(); j++) {
            fprintf(f," %i",fpts[j]);
        }
    }
    
    fprintf(f,"\nCELL_TYPES %i",fc->length());
    
    for (int i=0; i<fc->length(); i++) {
        if (i%30==0) {fprintf(f,"\n"); }
        unsigned int np = fc->getFace(i)->getPoints().size();
        if (np == 3) {
            fprintf(f," 5"); //VTK_TRIANGLE
        }
        else if (np == 4){ //VTK_QUAD
            fprintf(f," 9");
        }
    }
    
    fclose(f);
	
	delete fc;
	
}

int main(int argc,char** argv){
	
	if(argc==3){
		offToMdl(argv);
	}
	else {
		emsg();
		return 1;
	}
	
	return 0;
}

