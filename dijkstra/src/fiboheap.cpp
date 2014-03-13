#include "fiboHeap.h"
#include <cstddef>
#include <math.h>

#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

fiboHeap::fiboHeap(){
	min = NULL;
	nH = 0;
}

int fiboHeap::getMinKey(){
	return min->key;
}

fnode * fiboHeap::getMin(){
	return min;
}

int fiboHeap::numNodes(){
	return nH;
}

void fiboHeap::insert(int key){
	insert(new fnode(key));
}

void fiboHeap::insert(fnode *f){
	if(min == NULL){
		min = f;
		nH = 0;
	} else {
		min->insertRight(f);
		
		if(min->key > f->key)
			min = f;
	}
	nH = nH + 1;
}

fnode * fiboHeap::removeMin(){
	fnode *z = min;
	fnode *traverse;
	fnode *x;

	if(z != NULL)
		traverse = z->child;
	else
		return NULL;

	if(traverse != NULL){
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
		min = NULL;
	} else {
		min = z->right;
		this->consolidate(); //consolidate after removeMin
	}

	nH = nH - 1;
	delete z;
	return z;
}

void fiboHeap::consolidate(){
	
	int D = ceil(log(nH) / log(2));
	int d = 0; //degree
	
	//cout << "D : " << D << "min : "<<  min->key <<endl;
	fnode *A[D];

	for(int i = 0; i < D; i++)
		A[i] = NULL;

	fnode *traverse = min;
	fnode *x = NULL;
	fnode *y = NULL;
	fnode *temp = NULL;

	do{
		x = traverse;
		
		d = x->degree;
		//cout << "x: " << x->key << "degree in D : " << d << endl;
		while (A[d] != NULL){
			y = A[d];
			//cout << "(in while)y key : " << y->key << ", x : " << x->key << endl;
			if(x->key > y->key){
				temp = x;
				x = y;
				y = temp;
			}

			if(y == min)	//min should always point something in root list so that the do-while loop terminates
				min = x;

			//cout << "(in while)key before link : " << y->key << ", min : " << min->key <<endl;
			x->link(y);
			A[d] = NULL;
			d = d + 1;
			//cout << "(in while) after link degree : " << d << "x : " << x->key<< endl;
		}
		
		A[d] = x;
		traverse= x->right;
	}while(traverse != NULL && traverse != min);

	min = NULL; 

	for(int i = 0; i < D; i++){ //to set the new min 
		if(A[i] != NULL){
			if(min == NULL){
				min = A[i];
			} else if(min->key > A[i]->key){
				min = A[i];
			}
		}
	}

}

void fiboHeap::display(){ //needs to be enhanced
	fnode *traverse;
	if(min != NULL){
		traverse = min;
		cout << "root list : ";
		do{
			cout << traverse->key << "-->" ;
			traverse = traverse->right;
		}while(traverse != min);
		cout << traverse->key << endl;
	}
}


int main(){
	fiboHeap *fh = new fiboHeap();
	fh->insert(10);
	fh->insert(3);
	fh->insert(2);
	fh->insert(1);
	fh->insert(3);
	fh->insert(0);
	fh->insert(4);
	fh->insert(5);
	fh->display();
	cout << "min value: " << fh->getMinKey() << endl;
	cout << "No. of nodes before removeMin : " << fh->numNodes() << endl;
	fnode *min = fh->removeMin();
	cout << "remove min: " << min->key <<endl;
	cout << "new min : " << fh->getMinKey() << endl;
	cout << "total elements now : " << fh->numNodes() << endl;
	min = fh->removeMin();
	cout << "remove min: " << min->key <<endl;
	cout << "new min : " << fh->getMinKey() << endl;
	cout << "total elements now : " << fh->numNodes() << endl;
	fh->display();
	return 0;
}