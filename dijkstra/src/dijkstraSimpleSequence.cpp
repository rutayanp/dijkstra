/*============================================================================
* Name        : dijkstraSimpleSequence.cpp
* Author      : Rutayan Patro
* Version     :
* Copyright   : Please don't use it for assignments
* Description : Dijkstra's shortest path algorithm
*============================================================================*/

#include <iostream>
#include <string.h>

using namespace std;

enum state { visited, unvisited };

int * generateGraph(int n){
	int graph[81] = {0, 4, 0, 0, 0, 0, 0, 8, 0,
			         4, 0, 8, 0, 0, 0, 0, 11, 0,
	                 0, 8, 0, 7, 0, 4, 0, 0, 2,
	                 0, 0, 7, 0, 9, 14, 0, 0, 0,
	                 0, 0, 0, 9, 0, 10, 0, 0, 0,
	                 0, 0, 4, 0, 10, 0, 2, 0, 0,
	                 0, 0, 0, 14, 0, 2, 0, 1, 6,
	                 8, 11, 0, 0, 0, 0, 1, 0, 7,
	                 0, 0, 2, 0, 0, 0, 6, 7, 0};

	return graph;
}

int removeMin(int *dist, state *isvisited, int n){

	int min = INT_MAX;
	int min_index;

	for(int i = 0; i < n; i++){
		if (dist[i] < min && isvisited[i] == unvisited){
			min = dist[i];
			min_index = i;
		}
	}
	cout << min << endl;
	return min_index;
}

void stpSimpleSequence(int n, int x){

	int *graph = generateGraph(n); //to store the edges //implement the function
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
		for(int v = 0; v < n; v++){
			if((graph[u * n + v] != 0) && (isvisited[v] == unvisited) && (dist[v] >= (dist[u] + graph[u * n + v]))){
				dist[v] = dist[u] + graph[u * n + v];
			}
		}

	}

	for(int i = 0; i < n; i++){
		cout << i << "=> " << dist[i] << endl;
	}
}

int main(int argc, char *argv[]) {

	int n;
	int d;
	int x; //starting node
	/*if(strcmp(argv[1], "-r") == 0){

	} else if (strcmp(argv[1], "-s")){

	} else if (strcmp(argv[1], "-f")){

	}*/

	stpSimpleSequence(9, 0);
	return 0;
}
