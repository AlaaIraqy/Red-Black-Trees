#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
enum Color
{Red , Black};

class Node {
public:

    string val;
    Node* left, * right, * parent;
    bool Color;
    Node()
    {
        left = right = parent = NULL;
        Color=Red;
    }

    Node(string x) {
        val = x;
        left = right = parent = NULL;
        Color = Red;
    }
    /*bool isOnLeft() {
        return this == parent->left;
    }*/
    Node* grandparent(Node*node) {
        if (node->parent == NULL)
            return NULL;
        if (node->parent->parent == NULL)
            return NULL;

        return node->parent->parent;
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

        if (node-> parent->parent == NULL)
            return NULL;
        if (node->parent == node->grandparent(node)->right)
            return node->grandparent(node)->left;
        return node->grandparent(node)->right;
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
  /*  Node* ChangeColor(Node* node)
    {
        if (node->Color==Red)
            node->Color=Black;
        else
            node->Color = Red;

    }*/
};

   

    Node* ChangeColor(Node* node)
    {
        if (node->Color == Red)
            node->Color = Black;
        else
            node->Color = Red;
        return node;

    }

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

    Node* check(Node* node, Node* root)
    {
        if (node->parent == NULL)
        {
            node->Color = Black;
            return root; 
        }
        else
        {
            if (node->parent->Color == Black)
                return root;
            else
            {
                Node* uncle;
                if (node->parent->parent->left == node->parent)
                    uncle = node->parent->parent->right;
                else 
                {
                    uncle = node->parent->parent->left;
                }

                Node* grandparent = node->parent->parent;
                
                if (uncle==NULL||uncle->Color==Black)
                
                {
                    
                    
                    
                    
                        
                   

                    if (isLeft(node)&&isLeft(node->parent))
                    {
                        root =rightRotate(grandparent, root);
                       node->parent= ChangeColor(node->parent);
                        grandparent= ChangeColor(grandparent);
                        return root;
                    }
                    if (!isLeft(node) && isLeft(node->parent))
                    {
                        root=leftRotate(node->parent, root);
                        root=rightRotate(grandparent, root);
                      node->parent=  ChangeColor(node->parent);
                       grandparent= ChangeColor(grandparent);
                        return root;
                    }
                    if (!isLeft(node) && !isLeft(node->parent))
                    {

                       root= leftRotate(grandparent, root);
                       node->parent= ChangeColor(node->parent);
                       grandparent= ChangeColor(grandparent);
                        return root;

                    }
                    if (isLeft(node) && !isLeft(node->parent))
                    {
                       root= rightRotate(node->parent, root);
                         root= leftRotate(grandparent, root);
                           node->parent= ChangeColor(node->parent);
                           grandparent= ChangeColor(grandparent);
                            return root;
                    }
             }
                else
                {
                   node->parent= ChangeColor(node->parent);
                   uncle= ChangeColor(uncle);
                   if (grandparent->parent != NULL)
                   {
                       return check(ChangeColor(grandparent), root);

                   }
                   return root;

                }

                
               




                    
          
                    

            }

        }



    }

    Node* BSTInsert(Node* root, Node* node)
    {
       
        if (root == NULL)
            return node;

        if (node->val < root->val)
        {
            root->left = BSTInsert(root->left, node);
            root->left->parent = root;
        }
        else if (node->val > root->val)
        {
            root->right = BSTInsert(root->right, node);
            root->right->parent = root;
        }

       
        return root;
    }
    Node* insert(Node*root,string data)
    {
        Node* node = new Node(data);
        //Node* root=NULL;

        
        root = BSTInsert(root, node);

         
       return check (node,root);
       
    }

    int MAX(int x, int y)
    {
        if (x >= y)
            return x;
        else
            return y;
    }
    int height(Node* root)
    {
        return (root == NULL) ? -1 :
            1 + MAX(height(root->left), height(root->right));
    }
    int size(Node* root)
    {
        return (root == NULL) ? 0 :
            1 + size(root->left) + size(root->right);
    }



                



int main()
{
   /* Node* root=new Node("h");
    Node* right1 = new Node("d");
    Node* right2 = new Node("c");
    root->right = right1;
    right1->right = right2;
    Node* tree = root;
    cout << tree->val << endl;
    
    leftRotate(root, tree);
    cout << tree->left->val << endl;*/
    
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
    Node* root=NULL;
    root = insert(root, "h");
    root = insert(root, "d");
    root = insert(root, "b");
    //root = insert(root, "a");
  //  root = insert(root, "m");
    int x = size(root);
    int y = height(root);
    cout << x << endl;
    cout << y << endl;



        
     //   insert("abdo");


    
    //insert("zaghloul");
    cout << root->right->val << endl;
    
   



    

    
    return 0; 




}
