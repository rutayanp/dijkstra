/*
 * fiboHeap.h
 *
 *  Created on: Mar 7, 2014
 *      Author: rutayanpatro */
#ifndef FIBOHEAP_H_
#define FIBOHEAP_H_ 

#include "fiboHeap.h"
//#include "fiboNode.h"
#include <iostream>
#include <cstddef>

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
	~fnode();
	void insertRight(fnode *);
	void link(fnode *);
};

class fiboHeap{
	
	fnode *min;
	int nH;

public:
	fiboHeap();
	void insert(fnode *);
	void insert(int);
	int getMinKey();
	fnode *getMin();
	int numNodes();
	fnode *removeMin();
	void consolidate();
	void display();
	void decreaseKey(fnode *, int);
	void cut(fnode *);
	void cascadeCut(fnode *);
};

#endif /* FIBOHEAP_H_ */

