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
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

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
	void createGraphFile(vector<vector<int> >&);
};

graph::graph(int vertices, float density){
	n = vertices;
	e = (int)(density * vertices * (vertices - 1) / 200);
	cout << "edges : " << e << endl;
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
	for(int i = 0; i < n; i++ ){ 
			list[i].dest = i;
			list[i].weight = 0;
	}
}

int graph::random(int k){
	return rand() % k;
}

void graph::createGraph(){
	int i, j, weight;
	int k = 0;
	int flag_i = 0, flag_j = 0;
	bool isconnected = true;
	map<int, int> nodes_accounted;
	do{
		srand(time(NULL)); //1394919331 -- seed to create infinite loop
		//cout << time(NULL) << endl;
		while(k < e) {

			flag_i = 0;
			flag_j = 0;
			if(k < n)
				i = k;
			else
				i = random(n);
			j = random(n);
			weight = random(1000) + 1;

			nodes_accounted[i]++;
			nodes_accounted[j]++;

			if(i != j){

				if(list[j].neighbors.count(i) > 0) {// (j, i) already exists
					weight = list[j].neighbors[i];
				} else {
					list[j].neighbors[i] = weight; //if (j, i) doesn't exist then create one
				}

				if(list[i].neighbors.count(j) == 0){
					list[i].neighbors[j] = weight; //j is the destination and mapped to its weight forming i, j
					cout << "(" << k << ") " << i << ", " << j << " -- "<< list[i].neighbors[j] <<" ------- ";
					cout << "(" << k << ") " << j << ", " << i << " -- "<< list[j].neighbors[i] << endl;
					k++;
				}
			}
		}

		isconnected = true; //start with assuming the graph is connected
		for(int i = 0; i < n; i++){ //check if the graph is connected
			if(nodes_accounted.count(i) == 0){
				isconnected = false;
				cout << "isconnected : " << isconnected << endl;
				break;
			}
		}

		if(!isconnected){ //clear the graph if it is not connected
			cout << "cleared" << endl;
			for(int i = 0; i < n; i++ ){ 
				list[i].neighbors.clear();
				list[i].dest = i;
				list[i].weight = 0;
				nodes_accounted.clear();
				k = 0;
			}
		}
	}while(!isconnected);
}

void graph::createGraphFile(vector<vector<int> >& graphNodes){
	int i, j, weight;
	int k = 0;
	bool isconnected = true;
	for(int i = 0; i < e; i++){
		list[graphNodes[i][0]].neighbors[graphNodes[i][1]] = graphNodes[i][2];
		list[graphNodes[i][1]].neighbors[graphNodes[i][0]] = graphNodes[i][2];
		cout << "(" << i << ") " << graphNodes[i][0] << ", " << graphNodes[i][1] << " -- "<< list[graphNodes[i][0]].neighbors[graphNodes[i][1]] <<" ------- ";
		cout << "(" << i << ") " << graphNodes[i][1] << ", " << graphNodes[i][0] << " -- "<< list[graphNodes[i][1]].neighbors[graphNodes[i][0]] << endl;
	}
}

int graph::findWeight(int i, int j){
	return list[i].neighbors[j];
}

graph *dijkstraGraph(int n, int e){
	graph *g = new graph(n, e); //to store the edges 
	g->createGraph();
	return g;
}

graph *dijkstraGraph(int n, float d){
	graph *g = new graph(n, d); //to store the edges 
	g->createGraph();
	return g;
}

void readFile(vector<vector<int> >& graphNodes, string fileName, int & n, int & e){
	fstream fh;
	fh.open(fileName);
	string line;
	int u, v, weight;
//	fh>> numlines;
//	cout << numlines << endl;

	getline(fh, line);
	istringstream ss(line);
	cout << line << endl;
	fh>> n >> e;
	cout << n << ", " << e << endl;

	for(int i = 0; i < e; i++){
		fh >> u >> v >> weight;
		vector<int > temp;
		temp.push_back(u);
		temp.push_back(v);
		temp.push_back(weight);
		graphNodes.push_back(temp);
		//cout << graphNodes[i][0] << " " << graphNodes[i][1] << " " << graphNodes[i][2] << endl;
	}
}


/*int main(){
	int n = 0;
	int e = 0;
	vector<vector<int> > graphNodes;
	string fileName = "nodeedge.txt";
	readFile(graphNodes, fileName, n, e);
	graph *g = new graph(n, e);
	cout << "\n======\n" << endl;
	g->createGraphFile(graphNodes);
}*/