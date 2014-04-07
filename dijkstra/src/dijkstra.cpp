/*============================================================================
* HEADER FILES
*============================================================================*/
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <map>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <iterator>
#include <time.h>

//#define DEBUG
#define INT_MAX 214748364

enum state { visited, unvisited };

using namespace std;

/*============================================================================
 * Class prototypes
 *1) adjacency list node
 *2) undirected graph
 *3) fibonacci node
 *4) fibonacci heap
 *============================================================================*/

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
    ~graph();
	void createGraph();
	int random(int);
	int findWeight(int, int);
	void createGraphFile(vector<vector<int> >&);
    bool checkConnectivity();
    void dfsTraverse(int, map<int ,state>&);
};

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

public:
	fnode *min;
	int nH;
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
    void print(fnode *, fnode *);
    void clearHeap();
};

/*============================================================================
 ** This class defines the graphs based on the adjacency list
 ** The graph can be created using either a file or random number
 ** generator
 *============================================================================*/

/* Function : graph
 **
 ** Constructor to initialize the object of graph class
 ** Takes in arguments : vertices and density and calculates
 ** no. of edges based upon density.
 */
graph::graph(int vertices, float density){
	n = vertices;
	e = (int)(density * vertices * (vertices - 1) / 200);
	#ifdef DEBUG
    cout << "edges : " << e << endl;
    #endif
	list = new adjListNode[n];
	for(int i = 0; i < n; i++ ){ //point the next to NULL for each node
        list[i].dest = i;
        list[i].weight = 0;
	}
}


/* Function : graph
 **
 ** Constructor to initialize the object of graph class
 ** Takes in arguments : vertices and number of edges.
 ** Used when graph needs to be calculated based on the 
 ** inputs from the file.
 */
graph::graph(int vertices, int edges){
	n = vertices;
	e = edges;
	list = new adjListNode[n];
	for(int i = 0; i < n; i++ ){
        list[i].dest = i;
        list[i].weight = 0;
	}
}


/* Function : random
 **
 ** Random generator. Helper method to generate edges and random vertices.
 ** Takes in argument k and generates a random number between 0 and k.
 */
int graph::random(int k){
	return rand() % k;
}


/* Function : createGraph
 **
 ** This function creates graph based on n and e. After creating the graph
 ** it checks for the connectivity of the graph.
 ** If connected, graph is created; If not, graph is cleared and reinitialized
 */
void graph::createGraph(){
	int i, j, weight;
	int k = 0;
	int flag_i = 0, flag_j = 0;
	bool isconnected = true;
	map<int, int> nodes_accounted;
	do{
		srand(unsigned(time(NULL)) * 1000); //1394919331 -- seed to create infinite loop
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
					#ifdef DEBUG
                        cout <<  i << " " << j << " "<< list[i].neighbors[j] << endl; 
					#endif
                    k++;
				}
			}
		}
        
		isconnected = true; //start with assuming the graph is connected
        
        isconnected = checkConnectivity();
        
        if(!isconnected){ //clear the graph if it is not connected
			for(int i = 0; i < n; i++ ){
				list[i].neighbors.clear();
				list[i].dest = i;
				list[i].weight = 0;
				nodes_accounted.clear();
				k = 0;
            }
            
            sleep(2);
            #ifdef DEBUG
            cout << "====" << endl;
            #endif
        }
	}while(!isconnected);
}


/* Function : checkConnectivity
 **
 ** This function checks if the graph created is connected or not
 ** Uses a depth first search help function to traverse through the entire tree.
 */
bool graph::checkConnectivity(){
    map<int, state> node_visited;
    
    for(int i = 0; i < n; i++){
        node_visited[i] = unvisited;
    }
    
    dfsTraverse(0, node_visited);
    
    for(int i = 0; i < n; i++){
        if(node_visited[i] == unvisited)
            return false;
    }

    return true;
}

/* Function : dfsTraverse
 **
 ** This is a helper funtion which calls itself recursively to
 ** through all the nodes and marks all the visited nodes as
 ** visited.
 */
void graph::dfsTraverse(int vertex, map<int, state>& node_visited){
    node_visited[vertex] = visited;
    //cout << "visited: "<< vertex << endl; 
    for(map<int, int>::iterator i = list[vertex].neighbors.begin(); i != list[vertex].neighbors.end(); i++){
        if(node_visited[i->first] == unvisited)
            dfsTraverse(i->first, node_visited);
    }
}

/* Function : createGraphFile
 **
 ** Creates graph from a given file.
 */
void graph::createGraphFile(vector<vector<int> >& graphNodes){
	for(int i = 0; i < e; i++){
		list[graphNodes[i][0]].neighbors[graphNodes[i][1]] = graphNodes[i][2];
		list[graphNodes[i][1]].neighbors[graphNodes[i][0]] = graphNodes[i][2];
		//cout << "(" << i << ") " << graphNodes[i][0] << ", " << graphNodes[i][1] << " -- "<< list[graphNodes[i][0]].neighbors[graphNodes[i][1]] <<" ------- ";
		//cout << "(" << i << ") " << graphNodes[i][1] << ", " << graphNodes[i][0] << " -- "<< list[graphNodes[i][1]].neighbors[graphNodes[i][0]] << endl;
	}
}

/* Function : findWeight
 **
 ** Returns the weight of edge connecting node i and node j
 */
int graph::findWeight(int i, int j){
	return list[i].neighbors[j];
}

/* Function : ~graph
 **
 ** This is the destructor used to delete the graph once the distances are calculate.
 */
graph::~graph(){
    for(int i = 0; i < n; i++ ){
        list[i].neighbors.clear();
        list[i].dest = i;
        list[i].weight = 0;
    }
}

/*============================================================================
 * Methods of class fnode
 * These are the methods of the fibonacci node class
 *============================================================================*/

/* Function : fnode
 **
 ** Constructor for fnode class. Creates an empty node. 
 ** Parent initialized to null
 ** The sibling pointers point to itself.
 */
fnode::fnode(int ind, int k){
	key = k;
	index = ind;
	degree = 0;
	left = this;
	right = this;
	parent = NULL;
	child = NULL;
	childCut = false;
}

/* Function : delNode
 **
 ** This method sets all the pointers in the fnode to null. The address is
 ** present in the nodeadress data structure and can be freed once 
 ** application finishes
 */
void fnode::delNode(){
	parent = NULL;
	child = NULL;
	left = NULL;
	right = NULL;
}

/* Function : insertRight
 **
 ** This method connects node f as its right sibling.
 */
void fnode::insertRight(fnode *f){
    
	//assert(f != NULL);
	//assert(this != NULL);
	f->right = this->right;
	f->left = this;
	this->right->left = f;
	this->right = f;
}

/* Function : link
 **
 ** This method removes the node f, takes it and its subtrees out of the
 ** tree and connects it as a node of this node.
 */
void fnode::link(fnode *f){
	//assert(f != NULL);
	//assert(this != NULL);
	
    if(f->right != NULL)
        f->right->left = f->left;
	if(f->left != NULL)
        f->left->right = f->right;
	
    f->parent = this;
	
    if(this->child != NULL){
		this->child->insertRight(f);
		if(f->key < this->child->key)
			this->child = f;
	} else {
		this->child = f;
		f->right = f;
		f->left = f;
	}

	f->childCut = false;
	this->degree += 1;
}

/*============================================================================
 * Methods of class fibonacci Heap (fiboHeap class)
 *============================================================================*/

/* Function : fiboHeap
 **
 ** Constructor for fiboheap. Initializes the minimum to NULL.
 */
fiboHeap::fiboHeap(){
	min = NULL;
	nH = 0;
}

/* Function : getMinKey
 **
 ** This function returns the minimum key in the heap.
 */
int fiboHeap::getMinKey(){
	return min->key;
}

/* Function : getMinIndex
 **
 ** Returns the index of the minimum key in the heap.
 */
int fiboHeap::getMinIndex(){
	return min->index;
}

/* Function : getKey
 ** 
 ** Returns a fnode based on the index passed.
 */
int fiboHeap::getKey(int index){
	return nodeaddress[index]->key;
}

/* Function : getMin
 **
 ** Returns the node with the lowest key in the heap.
 */
fnode * fiboHeap::getMin(){
	return min;
}

/* Function : numNodes
 ** 
 ** Returns the number of nodes in the fibonacci heap.
 */
int fiboHeap::numNodes(){
	return nH;
}

/* Function : insert
 **
 ** This method inserts a fnode (fibonacci node) in the 
 ** root list of the heap.
 */
void fiboHeap::insert(int index, int key){
	fnode *f = new fnode(index, key);
	insert(f);
	nodeaddress.push_back(f);
}

/* Function : insert
 **
 ** This function is a helper function for insert. This inserts
 ** the fnode to the right of the min in the root list.
 */
void fiboHeap::insert(fnode *f){
	if(min == NULL){
		min = f;
        f->right = f;
        f->left = f;
		nH = 0;
	} else {
		min->insertRight(f);
        
		if(min->key > f->key)
			min = f;
	}
	nH = nH + 1;
}

/* Function : clearHeap
 **
 ** This method clears the heap based once the dijkstra finishes.
 */
void fiboHeap::clearHeap(){
    for(int i = 0; i < nodeaddress.size(); i++){
        nodeaddress[i]->delNode();
        delete nodeaddress[i];
    }
}

/* Function : removeMin
 **
 ** This method removes the minimum node from the fibonacci heap. 
 ** After removing the node it calls the consolidate function 
 ** to optimze on the finding the minimum node the next time.
 */
void fiboHeap::removeMin(){
	fnode *z = min;
	fnode *traverse = NULL;
	fnode *x = NULL;

    //assert(z != NULL);
    
	if(z != NULL)
		traverse = z->child;
    
	if(traverse != NULL){ //add all the children to the root list
		do{
			x = traverse;
			traverse = traverse->right;
            
			min->insertRight(x); //add x to the root by adding right to the min
			x->parent = NULL;
			if(min->key > x->key)
				min = x;
		}while(traverse != NULL && traverse != z->child);
	}
    
	//remove the old min stored in z
	z->right->left = z->left;
	z->left->right = z->right;
    
	if(z == z->right){
		//min = NULL;
	} else {
		min = z->right;
        consolidate(); //consolidate after removeMin
	}
    
	nH = nH - 1;
	z->delNode();
}

/* Function : consolidate
 **
 ** Consolidates the root list so that there is only one tree of a 
 ** particular degree in the root list.
 */
void fiboHeap::consolidate(){
    
	int D = ceil(log(nH) / log(2)) + 1;
	int d = 0; //degree
    
	fnode *A[D];
    
	for(int i = 0; i <= D; i++){
		A[i] = NULL;
    }

	fnode *traverse = min;
	fnode *x = NULL;
	fnode *y = NULL;
	fnode *temp = NULL;
    
    //break the link here so that it doesn't go into infinite loop
    min->left->right = NULL;
    min->left = NULL;
    
	do{
		x = traverse;
        
		d = x->degree;

        traverse = traverse->right;
        //assert(d <= D);
        //cout << "" ;
		
        while (A[d] != NULL){
			y = A[d];
			//cout << "(in while)y key : " << y->key << ", x : " << x->key << endl;
            
			if(x->key > y->key){
				temp = x;
				x = y;
				y = temp;
			}
            
            if(traverse == y)
                traverse = y->right;
            
			if(y == min)//min should always point something in root list so that the do-while loop terminates
				min = x;
            
            x->link(y);
			A[d] = NULL;
			d = d + 1;
			//cout << "(in while) after link degree : " << d << "x : " << x->key<< endl;
		}
        
		A[d] = x;
		//traverse= x->right;
	}while(traverse != NULL);
    
	min = NULL;
    
	for(int i = 0; i < D; i++){ //to set the new min
		if(A[i] != NULL){
            
            A[i]->left = A[i];
            A[i]->right = A[i];
            
			if(min == NULL){
				min = A[i];
			} else {
                min->insertRight(A[i]);
                if(min->key > A[i]->key)
                    min = A[i];
			}
		}
	}

   // delete[] A;
}

/* Function : decereaseKey
 **
 ** This method decreases the key of any node in the fibonacci heap.
 ** Once decreased to get the desired amortized complexity performs a 
 ** cascade cut operation.
 */
void fiboHeap::decreaseKey(int index, int k){
	fnode *x = nodeaddress[index];
	fnode *y = x->parent;
	if(x->key < k)
		throw "ERROR: new key greater than the old key";
	if(min == NULL)
		throw "ERROR: HEAP EMPTY";
    
	x->key = k;
	if(y != NULL && x->key < y->key){ //if x is a node in the root list or key(x) > key(parent of x)
        cut(x);
		cascadeCut(y);
	}
    
	if(min->key > x->key)
		min = x;
}

/* Function : cut
 **
 ** This method cuts the node x from the tree, directs the parent to null
 ** and performs cascadeCut if necessary.
 */
void fiboHeap::cut(fnode *x){
	fnode *y = x->parent;
	if(y->child == x){
		if(x->right == x)
			y->child = NULL;
		else
			y->child = x->right;
	}
    
	x->right->left = x->left; //to remove the node from the link
	x->left->right = x->right;
	y->degree -= 1; //decrease the degree of the parent after the child is removed
    
	min->insertRight(x);
	x->parent = NULL;
	x->childCut = false;
}

/* Function : cascadeCut
 **
 ** this removes the parent if the childCut flag is true
 ** i.e. if it has already lost one child after being the
 ** child of it's current parent.
 */
void fiboHeap::cascadeCut(fnode *y){
	fnode *z = y->parent;
	if(z == NULL) //base case : if the node is in the root list
		return;
    
	if(z != NULL){
		if(y->childCut){
			cut(y);
			cascadeCut(z); //call recursively progressing up towards the root list
		} else {
			y->childCut = true;
		}
	}
}

/* Function : display
 **
 ** This method displays the root list
 */
void fiboHeap::display(){ //needs to be enhanced displays only the root list
	fnode *traverse;
	if(min != NULL){
		traverse = min;
		cout << "root list : ";
		do{
			cout << traverse->key <<"(" << traverse->index << ")" << "-->" ;
			traverse = traverse->right;
		}while(traverse != min);
		cout << traverse->key << endl;
	}
}

/*============================================================================
 * Helper functions
 * 1) create graph based on no. of vertices and edges
 * 2) create graph based on no. of vertices and desnsity
 * 3) readfile to read the edge configuration for undirected graph
 *============================================================================*/


/* Function : dijkstraGraph
 **
 ** Creates a graph based on adjacency list consisting
 ** of n nodes and e edges.
 ** Returns a pointer to the graph object.
 */
graph *dijkstraGraph(int n, int e){
	graph *g = new graph(n, e); //to store the edges
	g->createGraph();
	return g;
}


/* Function : dijkstraGraph
 **
 ** Creates a graph based on adjacency list consisting
 ** of n nodes and d density.
 ** Returns a pointer to the graph object.
 */
graph *dijkstraGraph(int n, float d){
	graph *g = new graph(n, d); //to store the edges
	g->createGraph();
	return g;
}


/* Function : readFile
 **
 ** Reads a file to ceate a data structure indexed by source nodes
 ** and contains the respective destination and edge weights in the vector.
 ** It is basically a lookup table.
 */
void readFile(vector<vector<int> >& graphNodes, string filename, int & n, int & e, int &x){
	fstream fh;
	//filename = "/Users/rutayanpatro/Dropbox/ADS/adsproject/adsproject/" + filename;
	char *fname = new char[filename.length() + 1];
	strcpy(fname, filename.c_str());
	fh.open(fname, fstream::in);
	//assert(fh.is_open()); //check if the file is open
    
    string line;
	int u, v, weight;
    //	fh>> numlines;
    //	cout << numlines << endl;
    
	fh>> x;
	fh>> n >> e;
	//cout << n << ", " << e << endl;
    
	for(int i = 0; i < e; i++){
		fh >> u >> v >> weight;
		vector<int > temp;
		temp.push_back(u);
		temp.push_back(v);
		temp.push_back(weight);
		graphNodes.push_back(temp);
		#ifdef DEBUG
            cout << graphNodes[i][0] << " " << graphNodes[i][1] << " " << graphNodes[i][2] << endl;
	    #endif
    }
}

/*============================================================================
 * Name			: dijkstraSimpleSequence.cpp
 * Description	: Dijkstra's shortest path algorithm using fibonacci heap
 * Time			: O(nlogn + e)
 *============================================================================*/
void stpfibo(graph *g, int n, int x, bool display){
	
    if(n == 1){ //Number of vertices is 1
        cout << "0" << endl;
        exit(0);
    }
    
    fiboHeap *dist = new fiboHeap();
	int dist_u;
	int u;
    
	for(int i = 0; i < n; i++){
		dist->insert(i, INT_MAX);
	}
    
	dist->decreaseKey(x, 0);
    
	for(int i = 0; i < n; i++){
		dist_u = dist->getMinKey();
		u = dist->getMinIndex();
		//cout << "(" << i << ")(loop)to be removed index : " << dist->getMinIndex() << ", min : " << dist_u << endl;
		//dist->print(dist->min, dist->min->parent);
        dist->removeMin();
        //dist->print(dist->min, dist->min->parent); //print the fibheap
        //assert(dist->min != NULL);
        
		for(map<int, int>::iterator v = g->list[u].neighbors.begin(); v != g->list[u].neighbors.end(); v++){
			//cout << u << "-->" << v->first << " weight : " << v->second << endl;
			if(dist->getKey(v->first) > (dist_u + g->findWeight(u, v->first))){
                dist->decreaseKey(v->first, dist_u + g->findWeight(u, v->first));
                //dist->print(dist->min, dist->min->parent); //print the fibheap
                //cout << v->first << " : " << dist->getKey(v->first) << endl;
			}
			//cout << "2 : " << dist->getKey(2) << endl;
		}
        
	}

    if(display){
	    for(int i = 0; i < n; i++){
		    cout << dist->getKey(i) << endl;
	    }
    }
    dist->clearHeap();

}


/*============================================================================
 * Name        : dijkstraSimpleSequence.cpp
 * Description : Dijkstra's shortest path algorithm
 * Time			: O(n^2)
 *============================================================================*/
int removeMin(int *dist, state *isvisited, int n){
    
	int min = INT_MAX;
	int min_index;
    
	for(int i = 0; i < n; i++){
		if (dist[i] < min && isvisited[i] == unvisited){
			min = dist[i];
			min_index = i;
		}
	}
	//cout << min_index << endl;
	return min_index;
}

void stpSimpleSequence(graph *g, int n, int x, bool display){
    
    if(n == 1){
        cout << "0" << endl;
        exit(0);
    }
	
    int *dist = new int[n];
	state *isvisited = new state[n];
	int u;
    
	for(int i = 0; i < n; i++){
		dist[i] = INT_MAX;
		isvisited[i] = unvisited;
	}
    
	dist[x] = 0;
    
	for(int i = 0; i < n; i++){
		u = removeMin(dist, isvisited, n);
		isvisited[u] = visited;
		for(map<int, int>::iterator v = g->list[u].neighbors.begin(); v != g->list[u].neighbors.end(); v++){
			//cout << u << "-->" << v->first << " weight : " << v->second << endl;
			if(isvisited[v->first] == unvisited && (dist[v->first] > dist[u] + g->findWeight(u, v->first))){
				dist[v->first] = dist[u] + g->findWeight(u, v->first);
			}
		}
	}
    
    if(display){
        for(int i = 0; i < n; i++){
		    cout << dist[i] << endl;
	    }
    }
}

int main(int argc, char *argv[]) {
    
	int n = 0;
	float d = 0;
	int e = 0;
	vector<vector<int> > graphNodes;
	string filename;
	int x = 0; //starting node
	graph *g = NULL;
    
    //Performance Measurement parameters
    clock_t start_simple, start_fibo, end_simple, end_fibo, tot_time_simple = 0, tot_time_fibo = 0;
    
    //read command line options
    string runswitch;
    
    if(argc > 1)
        runswitch = argv[1];
    
    if(runswitch.compare("-r") == 0){ //prepare the test bench
        assert(argc == 5);
        
        n = atoi(argv[2]);
        d = atof(argv[3]);
        x = atoi(argv[4]);
        
        g = dijkstraGraph(n, d);
        assert(n != 0);
    
        start_simple = clock();
        stpSimpleSequence(g, n, x, true); //need to run 10 times and get an average out of the time of exec
        end_simple = clock();
    
        start_fibo = clock();
        //stpfibo(g, n, x, false);           //need to run 10 times and get an average out of the time of exec
        end_fibo = clock();
        
        delete g;
        //cout << (end_simple - start_simple) << endl;
        //cout << (end_fibo - start_fibo) << endl;
    
    } else if(runswitch.compare("-s") == 0){ //command line switch for running simple scheme
        assert(argc == 3);
        
        filename = argv[2];
        readFile(graphNodes, filename, n, e, x);
        g = new graph(n, e);
        g->createGraphFile(graphNodes);
        
        stpSimpleSequence(g, n, x, true);
    
    } else if(runswitch.compare("-f") == 0){ //command line argument for running fibonacci scheme
        assert(argc == 3);
        
        filename = argv[2];
        readFile(graphNodes, filename, n, e, x);
        g = new graph(n, e);
        g->createGraphFile(graphNodes);
        
        stpfibo(g, n, x, true);
    }
    
	return 0;
}

