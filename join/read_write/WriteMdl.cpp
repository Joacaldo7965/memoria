#include "WriteMdl.h"

WriteMdl::WriteMdl(string name){
    outname = name;
    outname+=".mdl\0";
    
}

WriteMdl::~WriteMdl(){
    //delete geometry;
}

void WriteMdl::writeHead(FILE *f){
    fprintf(f,"%s","[Name, STRING]\ntoto\n\n");
    fprintf(f,"%s","[Normals, ARRAY1<VECTOR3D>]\n1\n1 0 0\n\n");
}

void WriteMdl::writePoints(FILE *f, vector<Point> &points){
    int n = points.size();
    fprintf(f,"%s\n","[Vertices, ARRAY1<POINT3D>]");
    fprintf(f,"%i\n\n",n);
    
    for(int i=0;i<n;i++){
        Point p = points.at(i);
        if(p.getIndex()==-1){
            cout << "invalid index for a point in WriteMdl: -1\n";
        }
        fprintf(f," %+1.8E",p[0]);
        fprintf(f," %+1.8E",p[1]);
        fprintf(f," %+1.8E\n",p[2]);
    }
}


void WriteMdl::writeTriangleFaces(FILE *f, FaceContainer *fc){
    int n = fc->length(),triangulated=0;
    
    //count the number of triangles.
    for(int i=0;i<n;i++){
        Face *f = fc->getFace(i);
        triangulated += f->numberOfTriangles();
    }
    
    fprintf(f,"\n%s\n","[Triangles, ARRAY1<STRING>]");
    fprintf(f,"%i\n\n",triangulated);
    
    for(int i=0;i<n;i++){
        fc->getFace(i)->printTriangles(f);
    }
}

void WriteMdl::writeFaces(FILE *f, FaceContainer *fc){
    int n = fc->length(),triangulated=0,nt=0,ns=0;
    list<int> tri,squa,others;
    list<int>::iterator iter;
    
    //count the number of triangles and squares. Note: polygons
    //will be triangulated.
    for(int i=0;i<n;i++){
        Face *f = fc->getFace(i);
        int np = f->numberOfPoints();
        if(np==3){
            tri.push_back(i);
        }
        else if(np==4){
            squa.push_back(i);
        }
        else{
            others.push_back(i);
            triangulated += f->numberOfTriangles();
        }
    }
    
    nt = tri.size() + triangulated;
    ns = squa.size();
    
    //print the triangles if any.
    if(nt!=0){
        fprintf(f,"\n%s\n","[Triangles, ARRAY1<STRING>]");
        fprintf(f,"%i\n\n",nt);
        for(iter = tri.begin();iter!=tri.end();iter++){
            fc->getFace(*iter)->printFace(f);
            fprintf(f,"%s\n","0 0 0");
        }
        for(iter = others.begin();iter!=others.end();iter++){
            fc->getFace(*iter)->printTriangles(f);
        }
    }
    
    //print the squares if any.
    if(ns!=0){
        fprintf(f,"\n%s\n","[Squares, ARRAY1<STRING>]");
        fprintf(f,"%i\n\n",ns);
        for(iter = squa.begin();iter!=squa.end();iter++){
            fc->getFace(*iter)->printFace(f);
            fprintf(f,"%s\n","0 0 0");
        }
    }
}

void WriteMdl::execute(vector<Point> &points, FaceContainer *fc){
    FILE *f = fopen(outname.c_str(),"wt");
    
    writeHead(f);
    writePoints(f,points);
    writeFaces(f,fc);
    
    cout << "[WriteMdl] Points written: " << points.size() << endl;
    cout << "[WriteMdl] Faces written: " << fc->length() << endl;
    
    fclose(f);
}

void WriteMdl::writeOnlyPoints(vector<Point> &points){
    
    FILE *f = fopen(outname.c_str(),"wt");
    
    writeHead(f);
    writePoints(f,points);
    
    fclose(f);
}


void WriteMdl::writeWithTriangleFaces(vector<Point> &points, FaceContainer *fc){
    
    FILE *f = fopen(outname.c_str(),"wt");
    
    writeHead(f);
    writePoints(f,points);
    writeTriangleFaces(f,fc);
    
    fclose(f);
}
