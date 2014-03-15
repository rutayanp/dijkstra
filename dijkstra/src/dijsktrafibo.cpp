/*============================================================================
* Name			: dijkstraSimpleSequence.cpp
* Author		: Rutayan Patro
* Version		:
* Copyright		: Please don't use it for assignments
* Description	: Dijkstra's shortest path algorithm using fibonacci heap
* Time			: O(nlogn + e)
*============================================================================*/
#ifndef GRAPH_H_
#define GRAPH_H_
#include "graph.cpp"
#endif

#ifndef DIJKSTRASIMPLESEQUENCE_H_
#define DIJKSTRASIMPLESEQUENCE_H_
#include "dijkstraSimpleSequence.cpp"
#endif

#include "fiboheap.h"

#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

using namespace std;

void stpfibo(graph *g, int n, int x, float d){
	fiboHeap *dist = new fiboHeap();
	int dist_u;
	int u;
	int minKey;

	for(int i = 0; i < n; i++){
		dist->insert(i, INT_MAX);
	}

	//dist->display(); //debug
	dist->decreaseKey(x, 0);
	//cout << "new min : " << dist->getKey(x) << ", index : " << dist->getMinIndex() << endl; //debug
	//dist->display(); //debug

	for(int i = 0; i < n; i++){
		dist_u = dist->getMinKey();
		u = dist->getMinIndex();
		//cout << "(loop)min : " << dist_u << ", index : " << dist->getMinIndex() << endl; 
		dist->removeMin(); 
		
		for(map<int, int>::iterator v = g->list[u].neighbors.begin(); v != g->list[u].neighbors.end(); v++){
			//cout << u << "-->" << v->first << " weight : " << v->second << endl;
			if(dist->getKey(v->first) > (dist_u + g->findWeight(u, v->first))){
				dist->decreaseKey(v->first, dist_u + g->findWeight(u, v->first));
				//cout << v->first << " : " << dist->getKey(v->first) << endl;
			}
			//cout << "2 : " << dist->getKey(2) << endl;
		}
	}

	for(int i = 0; i < n; i++){
		cout << i << "=> " << dist->getKey(i) << endl;
	}
}


int main(int argc, char *argv[]) {

	int n = 4;
	float d = 25;
	int e = 3;
//	int x = 0; //starting node

	graph *g = dijkstraGraph(n, e);

	stpfibo(g, n, 2, d);
	cout << "\n======\n" <<endl;
	stpSimpleSequence(g, n, 2, d);

	return 0;
}
