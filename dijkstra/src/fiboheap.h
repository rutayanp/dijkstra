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
#include <vector>

class fnode{
	
public:
	int key;
	int index;
	fnode *left;
	fnode *right;
	fnode *parent;
	fnode *child;
	int degree;
	bool childCut;
	fnode(int, int);
	void delNode();
	void insertRight(fnode *);
	void link(fnode *);
};

class fiboHeap{
	
	fnode *min;
	int nH;

public:
	std::vector<fnode *> nodeaddress;
	fiboHeap();
	void insert(fnode *);
	void insert(int, int);
	int getMinKey();
	int getMinIndex();
	int getKey(int);
	fnode *getMin();
	int numNodes();
	void removeMin();
	void consolidate();
	void display();
	void decreaseKey(int, int);
	void cut(fnode *);
	void cascadeCut(fnode *);
};

#endif /* FIBOHEAP_H_ */

