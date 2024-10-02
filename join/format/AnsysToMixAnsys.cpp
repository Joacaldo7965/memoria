#include "AnsysToMixAnsys.h"

using namespace std;

void emsg(){
	cout << "use: ./ansys2quadansys input output\n";
	cout << "output will be written with extensions: node & elem\n";
}


void AnsysToMixAnsys(char** argv){
	
	ReadAnsys *ra;
	
	vector<Point> ansyspoints;
	vector<Element *> elements;
	
	ra = new ReadAnsys(argv[1]);
	ra->execute(ansyspoints,elements);
	delete ra;
    
    FileFormat *ansysformat = new AnsysFormat();
    
    //define output files
    string outnode = argv[2];
    string outelement = argv[2];
    outnode+=".node";
    outelement+=".elem";
    FILE *f_nodes = fopen(outnode.c_str(),"wt");
    FILE *f_elements = fopen(outelement.c_str(),"wt");
    
    for(unsigned int i=0; i<ansyspoints.size(); i++){
        Point aux = ansyspoints[i];

        fprintf(f_nodes,"%8i", i+1);
        fprintf(f_nodes," %+1.8E    ",aux[0]);
        fprintf(f_nodes," %+1.8E    ",aux[1]);
        fprintf(f_nodes," %+1.8E    \n",aux[2]);
    }
	   
	//insert into the set all element edges.
	for (unsigned int i=0; i<elements.size(); i++) {
        
        vector<int> e_nodes = elements[i]->getPoints();
        
        //print identyfier
        if (e_nodes.size()==4) {
            //print the element nodes
            for (unsigned int j=0; j<4; j++) {
                fprintf(f_elements,"%6i",e_nodes[j]+1);
            }
            
            fprintf(f_elements,"%6i%6i%6i%6i%6i%6i%6i%6i%6i%6i\n",0,0,0,0,1,1,1,1,0,i+1);
        }
        
        
        else {
            
            vector<int> aux = elements[i]->getPointsInFormat(ansysformat);
            for(int j=0;j<8;j++){
                fprintf(f_elements,"%6i",aux[j]);
            }
        
            if (e_nodes.size()==5) {
                fprintf(f_elements,"%6i%6i%6i%6i%6i%6i\n",4,4,4,1,0,i+1);
            }
            
            if (e_nodes.size()==6) {
                fprintf(f_elements,"%6i%6i%6i%6i%6i%6i\n",2,2,2,1,0,i+1);
            }
            
            if (e_nodes.size()==8) {
                fprintf(f_elements,"%6i%6i%6i%6i%6i%6i\n",3,3,3,1,0,i+1);
            }
        }
    }
	
    fclose(f_nodes);
    fclose(f_elements);
	
	for(int i=0;i<elements.size();i++)
		delete elements[i];
}

int main(int argc,char** argv){
	
	if(argc==3){
		AnsysToMixAnsys(argv);
	}
	else {
		emsg();
		return 1;
	}
	
	return 0;
}

