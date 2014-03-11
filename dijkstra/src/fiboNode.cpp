
#include "fiboHeap.h"

//#define DEBUG

#ifdef DEBUG
#include <iostream>
#include <stdlib.h>
#endif

#include <cstddef>

using namespace std;

fnode::fnode(int k){
	key = k;
	left = this;
	right = this;
	parent = NULL;
	child = NULL;
	degree = 0;
	childCut = false;
}

/*int main(){
	fiboNode *node = new fiboNode(10);
	return 0;
}*/