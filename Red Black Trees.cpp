#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
	string val;
	COLOR color;
	Node* left, * right, * parent;

	Node(string val) : val(val) {
		parent = left = right = NULL;
		color = RED;
	}
 
	Node* uncle() {
		if (parent == NULL or parent->parent == NULL)
			return NULL;

		if (parent->isOnLeft())		
			return parent->parent->right;
		else
			return parent->parent->left;
	}

	bool isOnLeft() {
		return this == parent->left; 
	}

	Node* sibling() {
	
		if (parent == NULL)
			return NULL;

		if (isOnLeft())
			return parent->right;

		return parent->left;
	}

	void moveDown(Node* nParent) {
		if (parent != NULL) {
			if (isOnLeft()) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild() {
		return (left != NULL and left->color == RED) or
			(right != NULL and right->color == RED);
	}
};

class RBTree {
public:
	Node* root;

	void leftRotate(Node* x) {
		
		Node* nParent = x->right;
		if (x == root)
			root = nParent;
		x->moveDown(nParent);
		x->right = nParent->left;
		if (nParent->left != NULL)
		nParent->left->parent = x;
		nParent->left = x;
	}

	void rightRotate(Node* x) {
		Node* nParent = x->left;
		if (x == root)
			root = nParent;
		x->moveDown(nParent);
		x->left = nParent->right;
		if (nParent->right != NULL)
			nParent->right->parent = x;
		nParent->right = x;
	}

	void swapColors(Node* x1, Node* x2) {
		COLOR temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValues(Node* u, Node* v) {
		string temp;
		temp = u->val;
		u->val = v->val;
		v->val = temp;
	}

	void fixRedRed(Node* x) {
		if (x == root) {
			x->color = BLACK;
			return;
		}

		Node* parent = x->parent, * grandparent = parent->parent,
			* uncle = x->uncle();

		if (parent->color != BLACK) {
			if (uncle != NULL && uncle->color == RED) {
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			}
			else {
				if (parent->isOnLeft()) {
					if (x->isOnLeft()) {
						swapColors(parent, grandparent);
					}
					else {
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					rightRotate(grandparent);
				}
				else {
					if (x->isOnLeft()){
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else {
						swapColors(parent, grandparent);
					}

					leftRotate(grandparent);
				}
			}
		}
	}


	RBTree() { 
		root = NULL;
	}

	Node* getRoot() {
		return root; 
	}

	Node* search(string val) {
		Node* temp = root;
		while (temp != NULL) {
			if (val < temp->val) {
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}
			else if (val == temp->val) {
				break;
			}
			else {
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}

		return temp;
	}

	void insert(string val) {
		Node* newNode = new Node(val);
		if (root == NULL) {
			newNode->color = BLACK;
			root = newNode;
		}
		else {
			Node* temp = search(val);

			if (temp->val == val) {
				cout << "word exists"<<endl;
				return;
			}
			newNode->parent = temp;

			if (val < temp->val)
				temp->left = newNode;
			else
				temp->right = newNode;
			fixRedRed(newNode);
		}
	}

	int size(Node *root)
	{
		return (root == NULL) ? 0 :
			1 + size(root->left) + size(root->right);
	}
	int height(Node* root)
	{
		return (root == NULL) ? -1 :
			1 + MAX(height(root->left), height(root->right));
	}
	int MAX(int x, int y)
	{
		if (x >= y)
			return x;
		else
			return y;
	}
};

int main() {
	RBTree tree;
	string word;
	ifstream file("dictionary.txt");
	if (file.is_open()) {
		while (getline(file, word)) {
			tree.insert(word);
		}
		file.close();
	}
	else
		cout << "file not found" << endl;
	string newWord;
	cout << "insert a word: ";
	cin >> newWord;
	tree.insert(newWord);
	cout << "Size: " << tree.size(tree.root) << endl;
	cout << "Height: " << tree.height(tree.root) << endl;
	
	return 0;
}
