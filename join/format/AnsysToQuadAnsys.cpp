#include "AnsysToQuadAnsys.h"

using namespace std;

void emsg(){
	cout << "use: ./ansys2quadansys input output\n";
	cout << "output will be written with extensions: node & elem\n";
}


void AnsysToQuadAnsys(char** argv){
	
	ReadAnsys *ra;
	
	vector<Point> ansyspoints;
	vector<Element *> elements;
	
	ra = new ReadAnsys(argv[1]);
	ra->execute(ansyspoints,elements);
	delete ra;
    
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
	
	set<AnsysQuadEdge> alledges;
	unsigned int node_idx = ansyspoints.size();
    
	//insert into the set all element edges.
	for (unsigned int i=0; i<elements.size(); i++) {
        
        vector<int> e_nodes = elements[i]->getPoints();
        
		for (int e_idx=0; e_idx<elements[i]->numberOfEdges(); e_idx++) {
			vector<int> e_edge = elements[i]->getEdge(e_idx);
			AnsysQuadEdge q_edge (e_edge[0],e_edge[1]);
			
			set<AnsysQuadEdge>::iterator my_edge = alledges.find(q_edge);
			//if the edge was not previously inserted:
			if (my_edge==alledges.end()) {
				//manage mid node index (in the edge)
                fprintf(f_nodes,"%8i", node_idx+1);
                //add the node to current vector of nodes
                e_nodes.push_back(node_idx);
                
				q_edge.setMidPoint(node_idx);
				node_idx++;
				alledges.insert(q_edge);
				//create the actual new mesh point and add it to the
				//vector of points.
				Point p1 = ansyspoints[e_edge[0]];
				Point p2 = ansyspoints[e_edge[1]];
				Point p3 = p1+p2;
				p3/=2;
                
                fprintf(f_nodes," %+1.8E    ",p3[0]);
                fprintf(f_nodes," %+1.8E    ",p3[1]);
                fprintf(f_nodes," %+1.8E    \n",p3[2]);
			}
            else {
                e_nodes.push_back((*my_edge)[2]);
            }
		}
        
        //print identyfier
        if (e_nodes.size()==20) {
            //print the element nodes
            for (unsigned int j=0; j<8; j++) {
                fprintf(f_elements,"%6i",e_nodes[j]+1);
            }
            fprintf(f_elements,"%6i%6i%6i%6i%6i%6i\n",3,3,3,1,0,i+1);
            //in a new line, continue to write the last mid-nodes
            for (unsigned int j=8; j<e_nodes.size(); j++) {
                fprintf(f_elements,"%6i",e_nodes[j]+1);
            }
            fprintf(f_elements,"\n");
        }
        if (e_nodes.size()==10) {
            //print the element nodes
            for (unsigned int j=0; j<8; j++) {
                fprintf(f_elements,"%6i",e_nodes[j]+1);
            }
            fprintf(f_elements,"%6i%6i%6i%6i%6i%6i\n",1,1,1,1,0,i+1);
            //in a new line, continue to write the last mid-nodes
            for (unsigned int j=8; j<e_nodes.size(); j++) {
                fprintf(f_elements,"%6i",e_nodes[j]+1);
            }
            fprintf(f_elements,"\n");
        }
        if (e_nodes.size()==15) {
            //print the element nodes

            fprintf(f_elements,"%6i",e_nodes[0]+1);
            fprintf(f_elements,"%6i",e_nodes[1]+1);
            fprintf(f_elements,"%6i",e_nodes[2]+1);
            fprintf(f_elements,"%6i",e_nodes[2]+1);
            fprintf(f_elements,"%6i",e_nodes[3]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[5]+1);
            fprintf(f_elements,"%6i",e_nodes[5]+1);

            fprintf(f_elements,"%6i%6i%6i%6i%6i%6i\n",2,2,2,1,0,i+1);
            
            fprintf(f_elements,"%6i",e_nodes[6]+1);
            fprintf(f_elements,"%6i",e_nodes[7]+1);
            fprintf(f_elements,"%6i",e_nodes[2]+1);
            fprintf(f_elements,"%6i",e_nodes[8]+1);
            fprintf(f_elements,"%6i",e_nodes[9]+1);
            fprintf(f_elements,"%6i",e_nodes[10]+1);
            fprintf(f_elements,"%6i",e_nodes[5]+1);
            fprintf(f_elements,"%6i",e_nodes[11]+1);
            fprintf(f_elements,"%6i",e_nodes[12]+1);
            fprintf(f_elements,"%6i",e_nodes[13]+1);
            fprintf(f_elements,"%6i",e_nodes[14]+1);
            fprintf(f_elements,"%6i\n",e_nodes[14]+1);
            
        }
        if (e_nodes.size()==13) {
            
            fprintf(f_elements,"%6i",e_nodes[0]+1);
            fprintf(f_elements,"%6i",e_nodes[1]+1);
            fprintf(f_elements,"%6i",e_nodes[2]+1);
            fprintf(f_elements,"%6i",e_nodes[3]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            
            fprintf(f_elements,"%6i%6i%6i%6i%6i%6i\n",4,4,4,1,0,i+1);
            
            fprintf(f_elements,"%6i",e_nodes[5]+1);
            fprintf(f_elements,"%6i",e_nodes[6]+1);
            fprintf(f_elements,"%6i",e_nodes[7]+1);
            fprintf(f_elements,"%6i",e_nodes[8]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[4]+1);
            fprintf(f_elements,"%6i",e_nodes[9]+1);
            fprintf(f_elements,"%6i",e_nodes[10]+1);
            fprintf(f_elements,"%6i",e_nodes[11]+1);
            fprintf(f_elements,"%6i\n",e_nodes[12]+1);
            
        }
        //in a new line, continue to write the last mid-nodes
        /*for (unsigned int j=8; j<e_nodes.size(); j++) {
            fprintf(f_elements,"%6i",e_nodes[j]+1);
        }
        fprintf(f_elements,"\n");*/
	}
	
    fclose(f_nodes);
    fclose(f_elements);
	
	for(int i=0;i<elements.size();i++)
		delete elements[i];
}

int main(int argc,char** argv){
	
	if(argc==3){
		AnsysToQuadAnsys(argv);
	}
	else {
		emsg();
		return 1;
	}
	
	return 0;
}

