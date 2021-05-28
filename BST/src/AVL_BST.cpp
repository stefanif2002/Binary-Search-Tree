#include "AVL_BST.h"
#include "BST.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

AVL_BST::AVL_BST()
{
    //ctor
}

AVL_BST::~AVL_BST()
{
    //dtor
}

int AVL_BST::maxHeight (node* ptr1, node* ptr2)
{
    if (ptr1 != NULL && ptr2 != NULL)
        return (ptr1->height > ptr2->height)? ptr1->height : ptr2->height;
    else if (ptr1 == NULL && ptr2 != NULL)
        return ptr2->height;
    else if (ptr1 != NULL && ptr2 == NULL)
        return ptr1->height;
    else
        return 0;
}

BST::node* AVL_BST::rightRotate(node* y)
{
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + maxHeight(y->left,y->right);
    x->height = 1 + maxHeight(x->left,x->right);

    return x;
}

BST::node* AVL_BST::leftRotate(node* x)
{
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + maxHeight(x->left,x->right);
    y->height = 1 + maxHeight(y->left,y->right);

    return y;
}

BST::node* AVL_BST::addLeafAVL (string a)
{
    return addLeafPrivateAVL (a, root);
}

BST::node* AVL_BST::addLeafPrivateAVL (string s, node* ptr)
{
    if (ptr == NULL)
        return createLeaf(s);

    if (s.compare(ptr->key) < 0) {
        if (ptr->left!=NULL)
            ptr->left = addLeafPrivateAVL(s, ptr->left);
        else
            ptr->left = createLeaf(s);
    }

    else if (s.compare(ptr->key) > 0) {
        if (ptr->right!=NULL)
            ptr->right = addLeafPrivateAVL(s, ptr->right);
        else
            ptr->right = createLeaf(s);
    }
    else {
        ptr->value++;
        return ptr;
    }

    ptr->height = 1 + maxHeight(ptr->left,ptr->right);

    int balance = isBalanced(ptr);

    if (balance > 1 && s.compare(ptr->left->key) < 0)
        return rightRotate(ptr);

    // Right Right Case
    if (balance < -1 && s.compare(ptr->right->key) > 0)
        return leftRotate(ptr);

    // Left Right Case
    if (balance > 1 && s.compare(ptr->left->key) > 0)
    {
        ptr->left = leftRotate(ptr->left);
        return rightRotate(ptr);
    }

    // Right Left Case
    if (balance < -1 && s.compare(ptr->right->key) < 0)
    {
        ptr->right = rightRotate(ptr->right);
        return leftRotate(ptr);
    }

    /* return the (unchanged) node pointer */
    return ptr;
}

BST::node* AVL_BST::deleteNodeAVL (string a)
{
    return deleteNodeAVL(a,root);
}

BST::node* AVL_BST::deleteNodeAVL (string a, node* ptr)
{
    if (root!=NULL) {
        if (root->key==a)
            removeNode (root);
        else {
            if (ptr->key.compare(a) > 0) {
                if (ptr->left!=NULL && ptr->left->key!=a){
                    ptr->left = deleteNodeAVL(a,ptr->left);
                }
                else if (ptr->left!=NULL && ptr->left->key==a){
                    removeNode (ptr, ptr->left, false);
                }
                else {
                    cout << "Element does not exist." << endl;
                    return ptr;
                }
            }
            if (ptr->key.compare(a) < 0) {
                if (ptr->right!=NULL && ptr->right->key!=a){
                    ptr->right = deleteNodeAVL(a,ptr->right);
                }
                else if (ptr->right!=NULL && ptr->right->key==a){
                    removeNode (ptr, ptr->right, true);
                }
                else {
                    cout << "Element does not exist." << endl;
                    return ptr;
                }
            }
        }
   }
   else {
    cout << "The tree is empty." << endl;
    return ptr;
   }

    ptr->height = 1 + maxHeight(ptr->left,ptr->right);

    int balance = isBalanced(ptr);

    if (balance > 1 && isBalanced(ptr->left) >= 0)
        return rightRotate(ptr);

    // Left Right Case
    if (balance > 1 && isBalanced(ptr->left) < 0)
    {
        ptr->left = leftRotate(ptr->left);
        return rightRotate(ptr);
    }

    // Right Right Case
    if (balance < -1 && isBalanced(ptr->right) <= 0) {
        node* temp = leftRotate(ptr);
        return temp;
    }

    // Right Left Case
    if (balance < -1 && isBalanced(ptr->right) > 0)
    {
        ptr->right = rightRotate(ptr->right);
        return leftRotate(ptr);
    }

    return ptr;
}

int AVL_BST::isBalanced (node* ptr)
{
    if (ptr->left != NULL && ptr->right != NULL)
        return ptr->left->height - ptr->right->height;
    else if (ptr->left == NULL && ptr->right != NULL)
        return -ptr->right->height;
    else if (ptr->left != NULL && ptr->right == NULL)
        return ptr->left->height;
    else
        return 0;

}

void AVL_BST::print (int c, long long int d)
{
    if (c==-1) {
        cout << "The tree is empty." << endl;
        return;
    }
    else if (c==0) {
        cout << "Element does not exist." << endl;
        return;
    }
    else if (c==1) {
        cout << "The element: "<< c << " has appeared 1 time in AVL Binary Search Tree." << endl;
        cout << "Duration of search in AVL Binary Search Tree equals " << d << " nanoseconds\n." << endl;
        return;
    }
    else {
        cout << "The element: "<< c << " has appeared " << c << " times in AVL Binary Search Tree." << endl;
        cout << "Duration of search in AVL Binary Search Tree equals " << d << " nanoseconds\n." << endl;
        return;
    }
}
