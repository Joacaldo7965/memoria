#include "FaceContainer.h"

FaceContainer::FaceContainer(){
	size=hashingsize=0;
}

FaceContainer::~FaceContainer(){
	for(int i=0;i<facesvec.size();i++)
		delete facesvec[i];
}

void FaceContainer::updatePointIndex(int oldp, int newp, list<int> &fs){
	list<int>::iterator iter;
	for(iter=fs.begin();iter!=fs.end();iter++){
		facesvec.at(*iter)->replacePoint(oldp,newp);
	}
}

Face *FaceContainer::getFace(int index){
	if(!outOfBoundary(index))
		return facesvec[index];
	return NULL;
}

int FaceContainer::length(){
	return size;
}

int FaceContainer::getFaceIndex(Face *f){
	int idx=f->getMinIndex();
	if(hashingsize>idx){
		list<int> local=hashing[idx];
		for(hashiter=local.begin();hashiter!=local.end();hashiter++)
			if(*facesvec[*hashiter]==*f)
				return *hashiter;
	}
	return -1;
}

int FaceContainer::addFace(Face *f){
	int find=getIndex(f);
	if(find!=-1){
		list<int> fe = f->getElements();
		list<int>::iterator iter;
		for (iter=fe.begin();iter!=fe.end();iter++)
			facesvec[find]->addElement(*iter);
		delete f;
		return find;
	}
	facesvec.push_back(f);
	return size++;
}

int FaceContainer::getIndex(Face *f){
	int idx=f->getMinIndex();
	if(hashingsize>idx){
		list<int> local=hashing[idx];
		for(hashiter=local.begin();hashiter!=local.end();hashiter++){
			if(*facesvec[*hashiter]==*f){
				return *hashiter;
			}
		}
		local.push_back(size);
		hashing[idx]=local;
		return -1;
	}
	else{
		list<int> local,voidlist;
		int i;
		for(i=hashingsize;i<idx;i++)
			hashing.push_back(voidlist);
		local.push_back(size);
		hashing.push_back(local);
		hashingsize=idx+1;
		return -1;
	}
}

int FaceContainer::outOfBoundary(int index){
	if(index>=size || index<0){
		cout << "Index out of boundary in face container! (" << index << "/";
		cout << size << ")" << endl;
		return 1;
	}
	return 0;
}

