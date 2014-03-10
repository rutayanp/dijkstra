#include "fiboNode.h"

#define DEBUG

#ifdef DEBUG
#include <iostream>
#include <stdlib.h>
#endif

using namespace std;

fiboNode::fiboNode(int d){
	value = d;
	child = NULL;
	parent = NULL;
	left = this;
	right = this;
	childCut = false;
}

fiboNode *fiboNode::insert(fiboNode * f){
	if (f == NULL)
		throw "(fiboNode::inser) Null pointer Exception\n";

	#ifdef DEBUG
	cout << "Appending " << f->getVal() << " to " << this->getVal() << endl;

	if(this = right.this){

	}
}

int main(){
	fiboNode *node = new fiboNode(10);
	return 0;
}