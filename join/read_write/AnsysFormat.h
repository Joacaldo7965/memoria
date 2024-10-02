#ifndef AnsysFormat_h
#define AnsysFormat_h 1

#include <vector>
#include "FileFormat.h"

using namespace std;

class AnsysFormat : public FileFormat {

  public:

	  AnsysFormat();

	  virtual ~AnsysFormat();

	  //Used to read from ansys and format in standar m3d
	  virtual vector<int> formatInputHexahedra(vector<int> &epoint);
	  
	  virtual vector<int> formatInputPrism(vector<int> &epoint);
	  
	  virtual vector<int> formatInputPyramid(vector<int> &epoint);
	  
	  virtual vector<int> formatInputTetrahedra(vector<int> &epoint);

	  //used to write in ansys and format from standar m3d to ansys
	  virtual vector<int> formatOutputHexahedra(vector<int> &epoint);
	  
	  virtual vector<int> formatOutputPrism(vector<int> &epoint);
	  
	  virtual vector<int> formatOutputPyramid(vector<int> &epoint);
	  
	  virtual vector<int> formatOutputTetrahedra(vector<int> &epoint);
	
};

#endif
