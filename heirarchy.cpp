#include <bits/stdc++.h>
using namespace std;

class Employee {
private:
int sup_id; // unique obj_id of the supervisor
int obj_id; // a unique id for the object, that helps maintain and identify the hierarchy (it won’t change)
int obj_val; /* the employee id needs to be stored here (it’s the data value
of the object, that may change). This is required to be printed/operated
on. */
Employee *left_subordinate;
Employee *right_subordinate;
// any other data members you require ..
public:
// your functions go here ..
	Employee(int id){
		obj_id = id;
		obj_val = id;

		left_subordinate = NULL;
		right_subordinate = NULL;
	}

	void setSubordinate(class Employee *ptr){
		if(left_subordinate == NULL)
			left_subordinate = ptr;
		else if(right_subordinate == NULL){
			right_subordinate = ptr;
		}
	}
	class Employee* getLeft (){ return left_subordinate; }
	class Employee* getRight(){ return right_subordinate; }
	int getVal(){return obj_val; }
	int getID(){return obj_id; }
	void setVal(int value){obj_val =value; }
};

class Tree
{
	int depth;	
	vector< class Employee* > v;
	class Employee* root;
public:

	void levelOrderTraversal(class Employee* node); //step 1

	void productEmployeeID(class Employee* node); //step 2

	void preOrderTraversal(class Employee* node); //step 3

	void incrementID(class Employee *node); //step 4
	//recursively set ID as sum of sub ordinates

	void inOrderTraversal(class Employee* node); //step 5

	//output line1
	int treeDepth(class Employee* node);

	Tree (int n){		
		int x;
		root = NULL;
		for (int i = 0; i < n; ++i)
		{
			class Employee* ptr = new Employee(i);			
			v.push_back(ptr);
		}
		for (int i = 0; i < n; ++i)
		{
			cin>>x;
			if(x != -1){
				v[x]->setSubordinate(v[i]);
			}
			else{
				root = v[i];
			}
		}
		//cout<<treeDepth(root)<< endl;
		//levelOrderTraversal(root);
		//productEmployeeID(root);
		//preOrderTraversal(root);
		//incrementID(root);
		//inOrderTraversal(root);
	} //end of constructor
};

void Tree::incrementID(class Employee* ptr){
	if(ptr == NULL) return;
	incrementID(ptr->getLeft());
	incrementID(ptr->getRight());

	//node has two children
	if(ptr->getLeft() != NULL && ptr->getRight() != NULL ){
		int s = ptr->getLeft()->getVal() + ptr->getRight()->getVal() ;
		if( s > ptr->getVal() ){
			ptr->setVal(s);
		}
		else if(s < ptr->getVal() ){
			//update left child ... only to be incremented
			int temp = ptr->getVal() - ptr->getRight()->getVal();		
			ptr->getLeft()->setVal(temp);
		}
	}
	//if node has only left child
	if(ptr->getLeft() != NULL && ptr->getRight() == NULL){
		int t = ptr->getLeft()->getVal();
		if(t < ptr->getVal()){
			ptr->getLeft()->setVal(ptr->getVal());
		}
		else if(t > ptr->getVal()){
			ptr->setVal(ptr->getLeft()->getVal());
		}
	}
}

void Tree::levelOrderTraversal(class Employee* node){
	
	if(!node) return;
	queue <class Employee* > q;
	class Employee* ptr = node;
	while(ptr){
		cout<<ptr->getVal()<<" ";
		if(ptr->getLeft())
			q.push(ptr->getLeft());
		if(ptr->getRight())
			q.push(ptr->getRight());
		ptr = q.front();
		q.pop();
	}
	
}

void Tree::productEmployeeID(class Employee* node){
	if(!node) return;
	queue <class Employee* > q;
	class Employee* ptr = node;
	q.push(ptr);
	int nodeCount = q.size();
	int i = 0;
	while(1){
		long long int prod = 1;
		nodeCount = q.size();
		if(!nodeCount) break;

		while(nodeCount){			
			ptr = q.front();
			//cout<<ptr->getVal()<<" ";
			prod *= ptr->getVal();
			q.pop();
			if(ptr->getLeft())
				q.push(ptr->getLeft());
			if(ptr->getRight())
				q.push(ptr->getRight());
			nodeCount--;
		}
		++i;
		cout<<i<<" "<<prod<<" ";
	}

}

void Tree::preOrderTraversal(class Employee* node){
	
	if(node == NULL) return;

	stack <class Employee* > nodeStack;
	nodeStack.push(node);

	class Employee* ptr;

	while( !nodeStack.empty() ){
		ptr = nodeStack.top();
		cout<<ptr->getVal()<<" "; 
		nodeStack.pop();

		if(ptr->getRight())
			nodeStack.push(ptr->getRight());

		if(ptr->getLeft())
			nodeStack.push(ptr->getLeft());
		
	}

}

void Tree::inOrderTraversal(class Employee* node){

	if(node == NULL) return;

	stack <class Employee* > nodeStack;

	class Employee* ptr = node;

	while(1){
		if( ptr != NULL){
			nodeStack.push(ptr);
			ptr = ptr->getLeft();
		}
		else{
			if(nodeStack.empty() == false){
				ptr = nodeStack.top();
				cout<<ptr->getVal()<<" ";
				nodeStack.pop();
				ptr = ptr->getRight();
			}
			else{
				break;
			}
		}
	}

}

int Tree::treeDepth(class Employee* node){
	if(node == NULL) return 0;
	//depth = max(depth left, depth right) + 1
	return( max(treeDepth(node->getRight()), treeDepth(node->getLeft()) ) +1) ;
} 

int main(int argc, char const *argv[])
{
	int n;
	cin>>n;
	class Tree T(n);
	return 0;
}