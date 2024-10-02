#include "WriteDolfinTriangleXML.h"

WriteDolfinTriangleXML::WriteDolfinTriangleXML(string name){
    outname = name;
    outname+=".xml\0";
    
}

WriteDolfinTriangleXML::~WriteDolfinTriangleXML(){
    //delete geometry;
}

void WriteDolfinTriangleXML::writePoints(FILE *f, vector<Point> &points){
    int n = points.size();
    
    fprintf(f,"    <vertices size=\"%i\">\n",n);

    for(int i=0;i<n;i++){
        Point p = points.at(i);
        fprintf(f,"      <vertex index=\"%i\" x=\"%f\" y=\"%f\" z=\"%f\" />\n",i,p[0],p[1],p[2]);
    }
    fprintf(f,"    </vertices>\n");
}

void WriteDolfinTriangleXML::writeElements(FILE *f, FaceContainer* fc){
    int n = fc->length();
    
    fprintf(f,"    <cells size=\"%i\">\n",n);
    
    for(int i=0;i<n;i++){
        vector<int> points = fc->getFace(i)->getPoints();
        fprintf(f,"      <triangle index=\"%i\"",i);
        for (int j=0; j<points.size(); j++) {
            fprintf(f," v%i=\"%i\"",j,points[j]);
        }
        fprintf(f,"/>\n");
    }
    
    fprintf(f,"    </cells>\n");
}

void WriteDolfinTriangleXML::execute(vector<Point> &points, FaceContainer* fc){
    FILE *f = fopen(outname.c_str(),"wt");
    
    fprintf(f,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n");
    fprintf(f,"<dolfin xmlns:dolfin=\"http://www.fenics.org/dolfin/\">\n");
    fprintf(f,"  <mesh celltype=\"triangle\" dim=\"2\">\n");
    
    writePoints(f,points);
    writeElements(f,fc);
    
    fprintf(f,"  </mesh>\n");
    fprintf(f,"</dolfin>\n");
    
    fclose(f);
}
