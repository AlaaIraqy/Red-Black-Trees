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
    bool isOnLeft() {
        return this == parent->left;
    }
    Node* sibling() {
        if (parent == NULL)
            return NULL;
        if (isOnLeft())
            return parent->right;
        if (!isOnLeft())
            return parent->left;
    }
    Node* uncle() {
        if (parent == NULL or parent->parent == NULL)
            return NULL;
        if (parent->isOnLeft())
            return parent->parent->right;
        else
            return parent->parent->left;
    }
};
class RBTree {
public:


};
int main()
{
    Node x("alaa");
    Node y("moh");
    Node z("omar");
    z.parent = &x;
    y.parent = &x;
    x.right = &y;
    x.left = &z;

    cout << y.sibling()->val;

}
