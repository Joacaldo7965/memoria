#ifndef FileFormat_h
#define FileFormat_h 1

#include <vector>

using namespace std;

class FileFormat {

  public:

	  //FileFormat();

	  virtual ~FileFormat()=0;

	  //Used to read from ansys and format in standar m3d
	  virtual vector<int> formatInputHexahedra(vector<int> &epoint)=0;
	  
	  virtual vector<int> formatInputPrism(vector<int> &epoint)=0;
	  
	  virtual vector<int> formatInputPyramid(vector<int> &epoint)=0;
	  
	  virtual vector<int> formatInputTetrahedra(vector<int> &epoint)=0;

	  //used to write in ansys and format from standar m3d to ansys
	  virtual vector<int> formatOutputHexahedra(vector<int> &epoint)=0;
	  
	  virtual vector<int> formatOutputPrism(vector<int> &epoint)=0;
	  
	  virtual vector<int> formatOutputPyramid(vector<int> &epoint)=0;
	  
	  virtual vector<int> formatOutputTetrahedra(vector<int> &epoint)=0;
	
};

inline FileFormat::~FileFormat(){

}

#endif
