/*============================================================================
* Name        : dijkstraSimpleSequence.cpp
* Author      : Rutayan Patro
* Version     :
* Copyright   : Please don't use it for assignments
* Description : Dijkstra's shortest path algorithm
*============================================================================*/

#include <iostream>
using namespace std;

enum state { visited, unvisited };

int * generateGraph(int n){

}

int removeMin(int *dist, state *isvisited){

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

		u = removeMin(dist, isvisited); //implementation required
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

int main() {
	cout << "trial" << endl; // prints trial
	return 0;
}
