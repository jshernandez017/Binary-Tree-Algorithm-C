#include <iostream>
#include <string.h>
#include <string>
using namespace std;
struct Node{//Node Structure
	int data;
	Node *left,*right,*parent;
	Node(): left(NULL),right(NULL),parent(NULL){}
	Node(int data) : data(data),left(NULL),right(NULL){}
	~Node(){
		delete left;
		delete right;
		delete parent;
	}
};
struct Tree{//Tree Structure
	Node *root;
	Tree() : root(NULL){}
	Tree(Node* head) : root(head){}
	~Tree(){delete root;}
};
Node *search(Node* root, int key){
	if(root->data == key || root == NULL)
		return root;
	if(root -> data > key)
		search(root->left,key);
	else
		search(root->right,key);
}
void displayTree(Node* root, int level, int direction){
    // Don't worry about this function, just use it
    if (root != NULL){
        displayTree(root->right, level+1, 1);
        
        for (int i = 0; i < level-1; i++) {
            std::cout << "   ";
        }
        if (level > 0 ){
            if (direction == 1){
                std::cout << " /--";
            }
            else{
                std::cout << " \\--";
            }
        }
        std::cout << root->data;
        std::cout << std::endl;
        level++;
        
        displayTree(root->left, level, -1);
    }
}

// Call the function to display the tree and leave some space afterwards
void drawTree(Node* root){
    displayTree(root, 0, 0);
    std::cout << std::endl << std::endl;
}
void ins(Tree* tree, Node* z){ //Insert Function from the book pg.294
	Node *y = NULL;
	Node *x = tree->root;
	while(x != NULL){
		y = x;
		if(z->data <= x->data)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if(y == NULL)
		tree->root = z;
	else if(z->data < y->data)
		y->left = z;
	else
		y->right = z;
}
Node * minVal(Node* node){ // Finds min value recursively of a Node
	Node* current = node; 
	while(current->left != NULL) 
		current = current->left; 
	return current; 
} 
Node *transplant(Tree *tree, Node *node, Node *succ){//Transplant Funtion from the book pg.296
	if(node->parent == NULL)
		tree->root = succ;
	else if(node == node->parent->left)
		node->parent->left = succ;
	else
		node->parent->right = succ;
	if(succ != NULL)
		succ->parent = node->parent;
}
void del(Tree *tree, Node *node){//Deletion Function from the book pg.298
	if(node ->left == NULL)
		transplant(tree,node,node->right);
	else if(node ->right == NULL)
		transplant(tree,node,node->left);
	else{
		Node *succ = minVal(node->right); //Find the minimum Successor
		if(succ->parent != node){
			transplant(tree,succ,succ->right);
			succ->right = node->right;
			succ->right->parent = succ;
		}
		transplant(tree,node,succ);
		succ->left = node->left;
		succ->left->parent = succ;
	}
} 
void prntPre(Node *root){//Print Pre Order Walk recursively
	if(root != NULL){
			cout << root->data << endl;
			prntPre(root->left);
			prntPre(root->right);
		}
	}
void prntPost(Node *root){//Print Post Order Walk recursively
	if(root != NULL){
		prntPost(root->left);
		prntPost(root->right);
		cout << root->data << endl;
	}
}	
void prntIn(Node *root){//Print In Order Walk recursively
	if(root != NULL){
		prntIn(root->left);
		cout << root->data << endl;
		prntIn(root->right);
	}	
}
int main(){ // Main in set to collect values from .txt file.
	Tree* tree = new Tree();
	string input;
	int key;
	while(input.compare("e")){
		cin >> input;
		string inte;
		string func;
		for(int i = 0; i < input.size();i++){
			if (isdigit(input[i]))
				 inte+=input[i];
			else
				func+=input[i];
		}
		key = atoi(inte.c_str());
		if(!func.compare("i"))
			ins(tree, new Node(key));
		if(!func.compare("d")){
			Node *temp = search(tree->root, key);
			if(temp != NULL)
				del(tree,temp);
		}
		if(!func.compare("opre"))
			prntPre(tree->root);
		if(!func.compare("opost"))
			prntPost(tree->root);
		if(!func.compare("oin"))
			prntIn(tree->root);
		drawTree(tree->root);
	}
	return 0;
}