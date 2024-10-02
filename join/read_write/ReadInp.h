#ifndef ReadInp_h
#define ReadInp_h 1

#include <string.h>
#include <stdlib.h>
#include <list>
#include "../geometry/Tetrahedra.h"

using namespace std;

class ReadInp {
  public:

	ReadInp(string name);

    virtual ~ReadInp();

    virtual bool execute(vector<Point> &vpoints, vector<Element *> &velements);

    virtual vector<double> getBounds();

  protected:

	virtual bool points(vector<Point> &vpoints);

	virtual bool elements(vector<Element *> &velements);
	
	virtual bool header(vector<Point> &vpoints, vector<Element *> &velements);
	
	virtual void readline();

  private:
   
    FILE *file;
    string name;    
    vector<double> bounds;

};

inline vector<double> ReadInp::getBounds(){
	return bounds;
}

#endif
