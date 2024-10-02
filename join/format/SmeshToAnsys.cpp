#include "SmeshToAnsys.h"

using namespace std;

void emsg(){
  cout << "use: ./smesh2ansys input output\n";
  cout << "output will be written with extensions: node & elem\n";
}

void ansysToAnsys(char** argv){
	ReadSmesh *rs;
	WriteAnsys *wa;
  
	vector<Point> points;
	vector<Element *> elements;
  
	rs = new ReadSmesh(argv[1]);
	rs->execute(points,elements);
	delete rs;
	
	cout << "file readed\n";
	cout.flush();
  
	  
	wa = new WriteAnsys(argv[2]);
	wa->execute(points,elements);
	delete wa;
  
	for(int i=0;i<elements.size();i++)
		delete elements[i];
}

int main(int argc,char** argv){

  if(argc==3){
    ansysToAnsys(argv);
  }
  else {
    emsg();
    return 1;
  }
  
  return 0;
}

