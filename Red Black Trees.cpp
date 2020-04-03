#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
class Node {
public:
    string val;
    Node* left, * right, * parent;
    bool black;

    Node(string x) {
        val = x;
        left = right = parent = NULL;
        black = false;
    }
    /*bool isOnLeft() {
        return this == parent->left;
    }*/
    Node* grandparent() {
        if (parent == NULL)
            return NULL;
        if (parent->parent == NULL)
            return NULL;

        return parent->parent;
}

   /* Node* sibling() {
        if (parent == NULL)
            return NULL;
        if (isLeft())
            return parent->right;
        if (!isLeft(Node))
            return parent->left;
    }*/
    Node* uncle(Node*node) {

        if ( parent->parent == NULL)
            return NULL;
        if (node->parent == node->grandparent()->right)
            return node->grandparent()->left;
        return node->grandparent()->right;
    }

    Node* createNode( string data)
    {
        Node* p = (Node*)malloc(sizeof(Node));
        p->val = data;
        p->right = NULL;
        p->left = NULL;


        return p;
    }

    bool isLeft(Node* node) {
        if (node->parent->left == node)
            return true;
        return false;
    }
};
class RBTree {
    
public:
    bool isLeft(Node* node) {
        if (node->parent->left == node)
            return true;
        return false;
    }
   

    
    Node* rightRotate(Node* node, Node* root)
    {
        
        if (node->left == NULL)
            return root;
        Node*child = node->left;
        node->left = child->right;
        child->parent = node->parent;
        if (child->right != NULL)
            child->right->parent = node;
        child->right = node;
        if (node->parent == NULL)
        {
            root = child;
        }
        else if (isLeft(node))
        {
            node->parent->right = child;
        }
        else node->parent->left = child;

        node->parent = child;
        
        return root;
    }

    Node* leftRotate(Node* node, Node* root)
    {

        if (node->right == NULL)
            return root;
        Node* child = node->right;
        node->right = child->left;
        child->parent = node->parent;
        if (child->left != NULL)
            child->left->parent = node;
        child->left = node;
        if (node->parent == NULL)
        {
            root = child;
        }
        else if (isLeft(node))
        {
            node->parent->left = child;
        }
        else node->parent->right = child;

        node->parent = child;

        return root;





    }


};
int main()
{
    Node* root=new Node("h");
    Node* right1 = new Node("d");
    Node* right2 = new Node("c");
    root->right = right1;
    right1->right = right2;
    Node* tree = root;
    cout << tree->val << endl;
    RBTree Rb;
    tree = Rb.leftRotate(root, tree);
    cout << tree->left->val << endl;
    
   /* Node* x("alaa");
    Node* y("moh");
    Node* z("omar");
    Node* m("Zaghloul");
    Node* a("Abdo");
    Node* root=NULL;*/
   /* x.parent = &m;
    m.parent = &x;
    x.parent = &y;
    m.right = &a;
    //x.left = &z;*/
   



    

    
    return 0; 




}
