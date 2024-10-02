#include "MdlToMdlTriangle.h"

using namespace std;

void emsg(){
  cout << "use: ./mdl2matlab input output\n";
  cout << "output automatically generated with extension mdl\n";
}

FaceContainer *triangulateFaces(FaceContainer *fc){
	FaceContainer *tfc = new FaceContainer();
	for(int i=0;i<fc->length();i++){
		vector<int> fpts = fc->getFace(i)->getPoints();
		if(fpts.size()==3){
			tfc->addFace(new Face(fpts));
		}
		else{
			vector<int> tf1(3,-1);
			vector<int> tf2(3,-1);
			tf1[0]=fpts[0];
			tf1[1]=fpts[1];
			tf1[2]=fpts[3];
			tfc->addFace(new Face(tf1));
			tf2[0]=fpts[1];
			tf2[1]=fpts[2];
			tf2[2]=fpts[3];
			tfc->addFace(new Face(tf2));
		}
	}
	return tfc;
}

void MdlToMdlT(char** argv){
  
	ReadMdl rmdl (argv[1]);
	WriteMdl wmdl (argv[2]);
  
	vector<Point> points;
	FaceContainer *fc = new FaceContainer();
  
	rmdl.execute(points,fc);
	
	FaceContainer *tri = triangulateFaces(fc);
	
	wmdl.execute(points,tri);

	cout << "> points " << points.size() << endl;
	cout << "> faces " << tri->length() << endl;

	delete fc;
	delete tri;
  
}

int main(int argc,char** argv){

  if(argc==3){
    MdlToMdlT(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

