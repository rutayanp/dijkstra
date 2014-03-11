/*
 * fiboNode.h
 *
 *  Created on: Mar 7, 2014
 *      Author: rutayanpatro */


#ifndef FIBONODE_H_
#define FIBONODE_H_

#include "fiboNode.h"

class fnode{
	
public:
	int key;
	fnode *left;
	fnode *right;
	fnode *parent;
	fnode *child;
	int degree;
	bool childCut;
	fnode(int);
};

#endif /* FIBONODE_H_ */

