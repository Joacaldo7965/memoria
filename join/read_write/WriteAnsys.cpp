#include "WriteAnsys.h"

WriteAnsys::WriteAnsys(string name){
    outname = name;
}

WriteAnsys::~WriteAnsys(){
}

bool WriteAnsys::execute(vector<Point> &points, vector<Element *> &elements){
    writeNodes(points);
    writeElements(elements);
    return true;
}

void WriteAnsys::writeNodes(vector<Point> &points){
    string outnode = outname;
    outnode+=".node";
    FILE *f = fopen(outnode.c_str(),"wt");
    cout << "number of points: " << points.size() << endl;
    for(int i=0;i<points.size();i++){
        Point aux = points[i];
        if(aux.getIndex()==-1)
            continue;
        fprintf(f,"%8i", i+1);
        fprintf(f," %+1.8E    ",aux[0]);
        fprintf(f," %+1.8E    ",aux[1]);
        fprintf(f," %+1.8E    \n",aux[2]);
    }
    fclose(f);
}

void WriteAnsys::writeElements(vector<Element *> &elements){
    string outnode = outname;
    FileFormat *ansysformat = new AnsysFormat();
    outnode+=".elem";
    int uniquetype=1;
    FILE *f = fopen(outnode.c_str(),"wt");
    cout << "number of elements: " << elements.size() << endl;
    for(int i=0;i<elements.size();i++){
        vector<int> aux = elements[i]->getPointsInFormat(ansysformat);
        for(int j=0;j<8;j++){
            fprintf(f,"%6i",aux[j]);
        }
        
        for (unsigned int j=0; j<3; j++) {
            fprintf(f,"%6i",elements[i]->getAnsysAuxType());
        }
        
        fprintf(f,"%6i%6i",1,0);
        fprintf(f,"%6i\n",(elements[i]->getIndex()+1));
    }
    
    fclose(f);
}

