#include "fiboHeap.cpp"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

fiboHeap::fiboHeap(){
	min = NULL;
}

void fiboHeap::insert(fiboNode *f){
	
	if(min == NULL){
		min = f;
	} else {
		if(find(f->getVal()) != NULL){
			throw "ERROR (fiboHeap::insert) : Duplicate value, Not allowed\n";
		}
		
	}
}


