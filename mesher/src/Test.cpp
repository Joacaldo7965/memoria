#include "Mesher.h"
#include "TriMesh.h"
#include "FEMesh.h"
#include "Services.h"
#include "RefinementCubeRegion.h"
#include "RefinementSurfaceRegion.h"
#include "RefinementInputSurfaceRegion.h"
#include "RefinementAllRegion.h"
#include "Point3D.h"
#include "EdgeInfo.h"
#include <string>
#include <cctype>
#include <time.h>
#include <chrono>

using std::atoi;
using std::cout;
using std::cerr;
using std::vector;
using std::string;
using std::map;
using Clobscode::RefinementRegion;
using Clobscode::RefinementCubeRegion;
using Clobscode::RefinementSurfaceRegion;
using Clobscode::Point3D;


void print_octant(Octant &o){
    cout << "Octant " << o.getIndex() << ": ";
    vector<unsigned int> pts = o.getPoints();
    cout << " Points: [";
    for (unsigned int i=0; i<pts.size(); i++) {
        cout << pts[i] << " ";
    }
    cout << "]" << endl;
}

void print_points(vector<MeshPoint> &points){
    cout << "Points: " << points.size() << endl;
    for (unsigned int i=0; i<points.size(); i++) {
        cout << "Point " << i << ": " << points[i].getPoint().print() << endl;
    }
}

vector<unsigned int> getSharedPoints(Octant &O1, Octant &O2){
    vector<unsigned int> epts1 = O1.getPoints();
    vector<unsigned int> epts2 = O2.getPoints();
    vector<unsigned int> shared_points;
    for (unsigned int i=0; i<epts1.size(); i++) {
        for (unsigned int j=0; j<epts2.size(); j++) {
            if (epts1[i] == epts2[j]) {
                shared_points.push_back(epts1[i]);
            }
        }
    }
    return shared_points;
}

void splitPoints(vector<MeshPoint> &points, vector<unsigned int> &shared_points){
    vector<MeshPoint> new_points;
    for (unsigned int i=0; i<shared_points.size(); i++) {
        Point3D p = points[shared_points[i]].getPoint();
        MeshPoint mp(p);
        new_points.push_back(mp);
    }
    points.insert(points.end(), new_points.begin(), new_points.end());
}

int main(int argc, char** argv){
    vector<MeshPoint> points;
    vector<unsigned int> epts1, epts2;
    for (unsigned int i=0; i<8; i++) {
        epts1.push_back(i);
        epts2.push_back(i+4);
    }
    MeshPoint mp;

    for (unsigned int i=0; i<3; i++) {
        Point3D p0(0,0,i);
        MeshPoint mp0(p0);
        points.push_back(mp0);

        Point3D p1(0,1,i);
        MeshPoint mp1(p1);
        points.push_back(mp1);

        Point3D p2(1,1,i);
        MeshPoint mp2(p2);
        points.push_back(mp2);

        Point3D p3(1,0,i);
        MeshPoint mp3(p3);
        points.push_back(mp3);
    }

    Octant O1(epts1, 0, 0);
    Octant O2(epts2, 0, 1);

    print_octant(O1);
    print_octant(O2);
    print_points(points);

    vector<unsigned int> indices_shared_points;

    // Detect shared points between octants
    indices_shared_points = getSharedPoints(O1, O2);

    cout << "Shared points: ";
    for (unsigned int i=0; i<indices_shared_points.size(); i++) {
        cout << indices_shared_points[i] << " ";
    }
    cout << endl;

    splitPoints(points, indices_shared_points);

    print_points(points);

    
    return 0;
}

void endMsg(){
	cout << "use: ./mesher [-d] input.mdl [-o] input.off [-u] output\n";
    cout << "              [-c] volume_mesh.oct (octant mesh to start from)\n";
    cout << "              [-s] ref_level [-a] ref_level [-b] file.reg [-l] list_file.txt\n";
    cout << "              [-r] input_surface rl [-g] [-v]\n";
	cout << "where:\n";
	cout << "  one of the parameters must be an input surface mesh in\n";
    cout << "  mdl or off format. If output name is not provided it\n";
	cout << "  will be saved in input_name.m3d. Options:\n";
	cout << "    -s Refine octants intersecting the input surface.\n";
    cout << "       Parameter ref_level is the refinement level\n";
    cout << "    -a Refine all elements in the input domain.\n";
    cout << "       Parameter ref_level is the refinement level\n";
	cout << "    -b Refine block regions provided in file file.reg\n";
    cout << "    -l Refine elements provided in the file by their index\n";
    cout << "    -r Refine surface region. Will refine all the elements\n";
    cout << "       in the provided input_surface at level rl\n";
    cout << "    -g save output mesh in GetFem format (gmf)\n";
    cout << "    -v save output mesh in VTK ASCII format (vtk)\n";
    cout << "    -i save output mesh in MVM ASCII format (mvm)\n";
    cout << "    -m save output mesh in M3D ASCII format (m3d)\n";
}


int main__(int argc,char** argv){

    if (argc<4) {
        endMsg();
        return 0;
    }
    
	//const int n_meshes = 1;
	string in_name = "", out_name = "";
	bool out_name_given = false, in_name_given = false;
	bool edge_projection = false;
	
	unsigned short ref_level = 0, rl = 0, cminrl=0, omaxrl=0;
    //cminrl: current min refinement level (used when starting from an Octree mesh)
    //omaxrl: old max refinement level (used when starting from an Octree mesh)
    list<unsigned int> roctli;
    //this list contains the index of the octants previously generated that need
    //one extra level of refinement.
    
	list<RefinementRegion *> all_regions;
    RefinementRegion *rr;

    vector<double> bounds;
    Point3D pmin,pmax;
    
    vector<Clobscode::TriMesh> inputs;
    inputs.reserve(4);
    //Clobscode::Services io;
    
    bool getfem=false, vtkformat=false, octant_start=false;
    bool m3dfor=false, mvmfor=false, oneout=false, plyfor=false;
    
    //for reading an octant mesh as starting point.
    vector<MeshPoint> oct_points;
    vector<Octant> oct_octants;
    map<OctreeEdge, EdgeInfo> edge_map;
    vector<unsigned int> oct_ele_link;
    GeometricTransform gt;
    
	for (unsigned int i=1; i<argc; i++) {
        
		if (argv[i][0]!='-') {
			cout << "Error: expected option -X and got " << argv[i] << "\n";
			endMsg();
			return 0;
		}
        
        bool inout = false;
        switch (argv[i][1]) {
            case 'g':
                getfem = true;
                oneout = true;
                continue;
                break;
            case 'v':
                vtkformat = true;
                oneout = true;
                continue;
                break;
            case 'm':
                m3dfor = true;
                oneout = true;
                continue;
            case 'i':
                mvmfor = true;
                oneout = true;
                continue;
            case 'p':
                plyfor = true;
                oneout = true;
                continue;
            default:
                break;
        }
        
		if (argc==i+1) {
			cout << "Error: expected argument for option " << argv[i] << "\n";
			endMsg();
			return 0;
		}
        
        switch (argv[i][1]) {
            case 'd':
                in_name = argv[i+1];

                if (!Services::ReadMdlMesh(in_name,inputs)) {
                    std::cerr << "couldn't read file " << argv[i+1] << std::endl;
                    return 1;
                }
                in_name_given = true;
                i++;
                break;
            case 'o':
                in_name = argv[i+1];
                
                if (!Services::ReadOffMesh(in_name,inputs)) {
                    std::cerr << "couldn't read file " << argv[i+1] << std::endl;
                    return 1;
                }
                in_name_given = true;
                i++;
                break;
            case 'u':
                out_name = argv[i+1];
                out_name_given = true;
                i++;
                break;
            case 'a':
                rl = atoi(argv[i+1]);
                if (ref_level<rl) {
                    ref_level = rl;
                }
                //+-10 is an arbitrary number to ensure the Bbox contains
                //the entire input mesh
                rr = new RefinementAllRegion(rl);
                
                //see if force rotation enable
                if (argv[i][2]=='r') {
                    rr->forceInputRotation();
                }
                
                all_regions.push_back(rr);
                i++;
                break;
            case 's':
                rl = atoi(argv[i+1]);
                if (ref_level<rl) {
                    ref_level = rl;
                }
                rr = new RefinementInputSurfaceRegion(rl);
                
                //see if force rotation enable
                if (argv[i][2]=='r') {
                    rr->forceInputRotation();
                }
                
                all_regions.push_back(rr);
                i++;
                break;
            case 'b':
                unsigned short max_reg;
                max_reg= Services::readRefinementRegions(argv[i+1],all_regions);
                if (ref_level<max_reg) {
                    ref_level = max_reg;
                }
                i++;
                break;
            case 'r':
                rl = atoi(argv[i+2]);
                Services::readSurfaceRefinementRegion(argv[i+1],all_regions,rl);
                if (ref_level<rl) {
                    ref_level = rl;
                }
                i+=2;
                break;
            case 'c':
                octant_start = true;
                Services::ReadOctreeMesh(argv[i+1], oct_points, oct_octants,
                                         edge_map,oct_ele_link,gt,cminrl,omaxrl);
                if (ref_level<omaxrl) {
                    ref_level = omaxrl;
                }
                i++;
                break;
            case 'l':
                if (octant_start) {
                    Services::ReadOctantList(argv[i+1],roctli,oct_ele_link);
                    /*list<unsigned int>::iterator oeiter;
                    for (oeiter=roctli.begin(); oeiter!=roctli.end(); oeiter++) {
                        rl = oct_octants[*oeiter].getRefinementLevel();
                        if (ref_level<=rl) {
                            ref_level = rl+1;
                        }
                    }*/
                }
                else {
                    cerr << "Warning: option -l needs a previously provided Octant";
                    cerr << " mesh (option -o) skipping\n";
                }
                i++;
                break;
            default:
                cerr << "Warning: unknown option " << argv[i] << " skipping\n";
                break;
        }
    }
    
    //cout << "max target rl: " << ref_level << endl;
    
    if (!in_name_given) {
        cerr << "No input domain surface mesh provided. Aborting\n";
        list<RefinementRegion *>::iterator rriter;
        for (rriter = all_regions.begin(); rriter!=all_regions.end(); rriter++) {
            delete *rriter;
        }
        return 0;
    }
	
	//give default output name if non is provided
	if (!out_name_given) {
		unsigned int last_point = in_name.find_last_of(".");
		out_name = in_name.substr(0,last_point);
	}
	
    auto start_time = chrono::high_resolution_clock::now();
    
    //Generate the mesh following the above constraints.
	Clobscode::Mesher mesher;
    Clobscode::FEMesh output;
    
    if (!octant_start) {
        output = mesher.generateMesh(inputs.at(0),ref_level,out_name,all_regions);
    }
    else {
        mesher.setInitialState(oct_points,oct_octants,edge_map);
        if (omaxrl<ref_level) {
            omaxrl = ref_level;
        }
        
        output = mesher.refineMesh(inputs.at(0),ref_level,out_name,roctli,
                                   all_regions,gt,cminrl,omaxrl);
    }
    
    
    if (getfem) {
        Services::WriteMeshGetfem(out_name,output);
    }

    if (vtkformat || !oneout) {
        Services::WriteVTK(out_name,output);
    }

    if (m3dfor) {
        Services::WriteOutputMesh(out_name,output);
    }

    if (mvmfor) {
        Services::WriteMixedVolumeMesh(out_name,output);
    }

    auto end_time = chrono::high_resolution_clock::now();
    cout << "  All done in " << chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
    cout << " ms"<< endl;
	
    list<RefinementRegion *>::iterator rriter;
    for (rriter = all_regions.begin(); rriter!=all_regions.end(); rriter++) {
        delete *rriter;
    }
    
	return 0;
}
