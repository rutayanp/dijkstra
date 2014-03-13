
#include "fiboHeap.h"

//#define DEBUG

#ifdef DEBUG
#include <iostream>
#include <stdlib.h>
#endif

#include <cstddef>

using namespace std;

fnode::fnode(int k, int index){
	key = k;
	index = 0;
	degree = 0;
	left = this;
	right = this;
	parent = NULL;
	child = NULL;
	childCut = false;
}

fnode::~fnode(){
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

fnode* fnode::findinSubtree(fnode *x, int index){
	fnode *res_node = NULL;
	fnode *traverse = NULL;
	if(x == NULL)
		return NULL;

	if(x->index == index)
		return x;

	traverse = x->child;
	while(traverse != x->child){
		res_node = findinSubtree(traverse, index);
		if(res_node != NULL)
			return res_node;
		traverse = traverse->right;
	}

}

/*int main(){
	fiboNode *node = new fiboNode(10);
	return 0;
}*/