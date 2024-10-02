#ifndef WriteOff_h
#define WriteOff_h 1

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include "../geometry/FaceContainer.h"
#include "../geometry/Point.h"

class WriteOff {
	
public:
	
	WriteOff(string name);
	
	virtual ~WriteOff();
	
	//wirte a mdl file with square and trinagle faces
	virtual void execute(vector<Point> &points,
						 FaceContainer *fc);
	
	virtual void execute(vector<Point> &points,
						 FaceContainer *fc,
						 bool color_option);
	
	virtual void execute(vector<Point> &points, 
						 vector<vector<unsigned int> > &faces);
	
protected:
	
	virtual void writeHead(FILE *f);
	
	virtual void writePoints(FILE *f, vector<Point> &points);
	
	virtual void writeFaces(FILE *f, FaceContainer *fc,
							bool color_option);
	
	virtual void writeFaces(FILE *f, vector<vector<unsigned int> > &faces);
	
protected:
	
	string outname;
	
};

#endif
