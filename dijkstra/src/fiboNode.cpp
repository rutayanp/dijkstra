
#include "fiboHeap.h"

//#define DEBUG

#ifdef DEBUG
#include <iostream>
#include <stdlib.h>
#endif

#include <cstddef>

using namespace std;

fnode::fnode(int ind, int k){
	key = k;
	index = ind;
	degree = 0;
	left = this;
	right = this;
	parent = NULL;
	child = NULL;
	childCut = false;
}

void fnode::delNode(){
	parent = NULL;
	child = NULL;
	left = NULL;
	right = NULL;
}

void fnode::insertRight(fnode *f){
	f->right = this->right;
	f->left = this;
	this->right->left = f;
	this->right = f;
}

void fnode::link(fnode *f){
	f->right->left = f->left;
	f->left->right = f->right;
	f->parent = this;
	if(this->child != NULL){
		this->child->insertRight(f);
		if(f->key < this->child->key)
			this->child = f;

	} else {
		this->child = f;
		f->right = f;
		f->left = f;
	}
	f->childCut = false;
	this->degree += 1;
}

/*int main(){
	fiboNode *node = new fiboNode(10);
	return 0;
}*/