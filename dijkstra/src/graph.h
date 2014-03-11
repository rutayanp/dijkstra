/*
 * graph.h

 *
 *  Created on: Mar 8, 2014
 *      Author: rutayanpatro
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <map>

//#include "graph.h"


struct adjListNode{
	int dest;
	int weight;
	std::map<int , int> neighbors; //destination mapped to weight from source to that node
};

class graph{

public:
	int n;
	int e;
	adjListNode *list;

	graph(int, int);
	graph(int, float);
	void createGraph();
	void printGraph(int);
	int random(int);
	int findWeight(int, int);
};

#endif /* GRAPH_H_ */
