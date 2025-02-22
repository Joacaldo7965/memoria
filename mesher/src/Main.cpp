/*
 <Mix-mesher: region type. This program generates a mixed-elements mesh>
 
 Copyright (C) <2013,2017>  <Claudio Lobos>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/gpl.txt>
 */

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
#include <sys/resource.h> //rusage

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

//-------------------------------------------------------------------
//-------------------------------------------------------------------

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

//-------------------------------------------------------------------
//-------------------------------------------------------------------

int main(int argc, char** argv){
	
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

    // splitPoints variables
    bool use_split_points = false;
    bool use_surface_patterns = false;
    float split_kappa = 0.6;
    float split_delta = 90.0;
    
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
                if (argv[i][2]=='s') {
                    use_surface_patterns = true;
                    // i++;
                    continue;
                }
                plyfor = true;
                oneout = true;
                continue;
            default:
                break;
        }
        
		if (argc==i+1) {
            if(!((argv[i][1] == 's' && argv[i][2] == 'p') || (argv[i][1] == 'p' && argv[i][2] == 's'))){
                cout << "Error: expected argument for option " << argv[i] << "\n";
                endMsg();
                return 0;
            }
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
                if(argv[i][2]=='p'){
                    use_split_points = true;
                    i++;
                    break;
                }else if(argv[i][2] == 'd'){
                    split_delta = atof(argv[i+1]);
                    cout << "  Split delta: " << argv[i+1] << endl;
                    i++;
                    break;
                }

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
            case 'k':
                split_kappa = atof(argv[i+1]);
                cout << "  Split kappa: " << argv[i+1] << endl;
                
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

    cout << "  Using SplitPoints? " << use_split_points << endl;
    cout << "  Using Surface Patterns? " << use_surface_patterns << endl;
	
    cout << "  Starting generation/refinement\n";
    auto start_time = chrono::high_resolution_clock::now();
    
    //Generate the mesh following the above constraints.
	Clobscode::Mesher mesher;
    Clobscode::FEMesh output;
    
    if (!octant_start) {
        output = mesher.generateMesh(inputs.at(0),ref_level,out_name,all_regions, use_surface_patterns, use_split_points, split_kappa, split_delta);
    }
    else {
        mesher.setInitialState(oct_points,oct_octants,edge_map);
        if (omaxrl<ref_level) {
            omaxrl = ref_level;
        }
        
        output = mesher.refineMesh(inputs.at(0),ref_level,out_name,roctli,
                                   all_regions,gt,cminrl,omaxrl);
    }
    
    auto gen_time = chrono::high_resolution_clock::now();
    cout << "  Generation done (#"<< output.getElements().size() << ") in " << std::chrono::duration_cast<chrono::milliseconds>(gen_time-start_time).count();
    cout << " ms"<< endl;

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
    cout << "  Write done in " << std::chrono::duration_cast<chrono::milliseconds>(end_time-gen_time).count();
    cout << " ms"<< endl;
    cout << "  All done in " << std::chrono::duration_cast<chrono::milliseconds>(end_time-start_time).count();
    cout << " ms"<< endl;

    struct rusage myusage;
      if (getrusage(RUSAGE_SELF, &myusage)==-1)
                { cerr << "Error getrusage\n"; }
    cout << " Memory Usage (max resident memory) " << myusage.ru_maxrss;
    cout << " kB (" << myusage.ru_maxrss/1024 << " MB)"<< endl;
	
    list<RefinementRegion *>::iterator rriter;
    for (rriter = all_regions.begin(); rriter!=all_regions.end(); rriter++) {
        delete *rriter;
    }
    
	return 0;
}

