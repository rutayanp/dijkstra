/*============================================================================
* Name        : dijkstraSimpleSequence.cpp
* Author      : Rutayan Patro
* Version     :
* Copyright   : Please don't use it for assignments
* Description : Dijkstra's shortest path algorithm
* Time			: O(n^2)
*============================================================================*/

#include "graph.cpp"
#define DEBUG

#ifdef DEBUG
#include <iostream>

//using namespace std;

enum state { visited, unvisited };
#endif

int removeMin(int *dist, state *isvisited, int n){

	int min = INT_MAX;
	int min_index;

	for(int i = 0; i < n; i++){
		if (dist[i] < min && isvisited[i] == unvisited){
			min = dist[i];
			min_index = i;
		}
	}
	cout << min_index << endl;
	return min_index;
}

void stpSimpleSequence(int n, int x, float d){

	graph *g = new graph(n, d); //to store the edges //implement the function
	g->createGraph();
	int *dist = new int[n];
	state *isvisited = new state[n];
	int u;

	for(int i = 0; i < n; i++){
		dist[i] = INT_MAX;
		isvisited[i] = unvisited;
	}

	dist[x] = 0;

	for(int i = 0; i < n; i++){
		u = removeMin(dist, isvisited, n); //implementation required
		isvisited[u] = visited;
		for(map<int, int>::iterator v = g->list[u].neighbors.begin(); v != g->list[u].neighbors.end(); v++){
			cout << u << "-->" << v->first << " weight : " << v->second << endl;
			if(isvisited[v->first] == unvisited && (dist[v->first] > dist[u] + g->findWeight(u, v->first))){
				dist[v->first] = dist[u] + g->findWeight(u, v->first);
			}
		}

	}

	for(int i = 0; i < n; i++){
		cout << i << "=> " << dist[i] << endl;
	}
}


int main(int argc, char *argv[]) {

	int n = 9;
	float d = 25;
//	int e = 9;
//	int x = 0; //starting node

	stpSimpleSequence(n, 0, d);
	return 0;
}
