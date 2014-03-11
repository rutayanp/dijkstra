#include "fiboHeap.h"
#include <cstddef>

#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

fiboHeap::fiboHeap(){
	min = NULL;
	nH = 0;
}

int fiboHeap::getMinKey(){
	return min->key;
}

fnode * fiboHeap::getMin(){
	return min;
}

int fiboHeap::numNodes(){
	return nH;
}

void fiboHeap::insert(int key){
	insert(new fnode(key));
}

void fiboHeap::insert(fnode *f){
	if(min == NULL){
		min = f;
		nH = 0;
	} else {
		f->right = min->right;
		f->left = min;
		min->right->left = f;
		min->right = f;
		
		if(min->key > f->key)
			min = f;
	}
	nH = nH + 1;
}

void fiboHeap::removeMin(){
	fnode *z = min;
	fnode *temp = z->child;

	temp->parent = NULL;
	temp = temp->right;
	while(temp != NULL && temp != z->child){
		
	}
}



int main(){
	fiboHeap *fh = new fiboHeap();
	fh->insert(10);
	fh->insert(6);
	cout << fh->getMinKey() << endl;
	cout << fh->numNodes() << endl;
	return 0;
}