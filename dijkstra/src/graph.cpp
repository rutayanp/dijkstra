/*============================================================================
* Name        : graph.cpp
* Author      : Rutayan Patro
* Version     :
* Copyright   : Please don't use it for assignments
* Description : graph based on adjacency list
*============================================================================*/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <map>


#ifdef DEBUG
enum state { visited, unvisited };
#endif

using namespace std;
struct adjListNode{
	int dest;
	int weight;
	map<int , int> neighbors; //destination mapped to weight from source to that node
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

graph::graph(int vertices, float density){
	n = vertices;
	e = (int)(density * vertices * (vertices - 1) / 200);
	list = new adjListNode[n];
	for(int i = 0; i < n; i++ ){ //point the next to NULL for each node
			list[i].dest = i;
			list[i].weight = 0;
	}
}

graph::graph(int vertices, int edges){
	n = vertices;
	e = edges;
	list = new adjListNode[n];
	for(int i = 0; i < n; i++ ){ //point the next to NULL for each node
			list[i].dest = i;
			list[i].weight = 0;
	}
}

int graph::random(int k){
	return rand() % k;
}

void graph::createGraph(){
	int i, j, weight;
	srand(time(NULL));
	int k = 0;
	int flag_i = 0, flag_j = 0;
	while(k < e) {
		flag_i = 0;
		flag_j = 0;
		if(k < n)
			i = k;
		else
			i = random(n);
		j = random(n);
		weight = random(1000) + 1;

		if(i != j){

			if(list[j].neighbors.count(i) > 0) {// (j, i) already exists
				weight = list[j].neighbors[i];
			} else {
				list[j].neighbors[i] = weight; //if (j, i) doesn't exist then create one
			}

			if(list[i].neighbors.count(j) == 0){
				list[i].neighbors[j] = weight; //j is the destination and mapped to its weight forming i, j
				cout << "(" << k << ") " << i << ", " << j << " -- "<< list[i].neighbors[j] <<" ------- ";
				cout << "(" << k << ") " << j << ", " << i << " -- "<< list[j].neighbors[i] <<endl;
				k++;
			}
		}
	}
}

int graph::findWeight(int i, int j){
	return list[i].neighbors[j];
}

void graph::printGraph(int s){

}

/*
int main(int argc, char *argv[]) {

	int n = 9;
	float d = 22.23;
	int e = 9;
	int x = 0; //starting node

	graph *g;
	g = new graph(n, d);
	g->createGraph();
	g->printGraph(x);
	cout << endl << endl;
	for(int u = 0; u < n; u++){
		for(map<int, int>::iterator v = g->list[u].neighbors.begin(); v != g->list[u].neighbors.end(); v++){
			cout << u << ", " << v->first<< " ---- " << v->second << endl;
		}
	}
	//stpSimpleSequence(9, 0);
	return 0;
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
*/
