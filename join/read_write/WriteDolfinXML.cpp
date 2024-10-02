#include "WriteDolfinXML.h"

WriteDolfinXML::WriteDolfinXML(string name){
    outname = name;
    outname+=".xml\0";
    
}

WriteDolfinXML::~WriteDolfinXML(){
    //delete geometry;
}

void WriteDolfinXML::writePoints(FILE *f, vector<PointM3d> &points){
    int n = points.size();
    
    fprintf(f,"    <vertices size=\"%i\">\n",n);

    for(int i=0;i<n;i++){
        PointM3d p = points.at(i);
        fprintf(f,"      <vertex index=\"%i\" x=\"%f\" y=\"%f\" z=\"%f\" />\n",i,p[0],p[1],p[2]);
    }
    fprintf(f,"    </vertices>\n");
}

void WriteDolfinXML::writeElements(FILE *f, vector<Element *> &elements){
    int n = elements.size();
    
    fprintf(f,"    <cells size=\"%i\">\n",n);
    
    for(int i=0;i<n;i++){
        vector<int> points = elements.at(i)->getPoints();
        fprintf(f,"      <tetrahedron index=\"%i\"",i);
        for (int j=0; j<points.size(); j++) {
            fprintf(f," v%i=\"%i\"",j,points[j]);
        }
        fprintf(f,"/>\n");
    }
    
    fprintf(f,"    </cells>\n");
}

void WriteDolfinXML::execute(vector<PointM3d> &points, vector<Element *> &elements){
    FILE *f = fopen(outname.c_str(),"wt");
    
    fprintf(f,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n");
    fprintf(f,"<dolfin xmlns:dolfin=\"http://www.fenics.org/dolfin/\">\n");
    fprintf(f,"  <mesh celltype=\"tetrahedron\" dim=\"3\">\n");
    
    writePoints(f,points);
    writeElements(f,elements);
    
    fprintf(f,"  </mesh>\n");
    fprintf(f,"</dolfin>\n");
    
    fclose(f);
}
