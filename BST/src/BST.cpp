#include <cstdlib>
#include <iostream>
#include "BST.h"
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

BST::BST()
{
    root = NULL;
}

BST::~BST()
{
    removeSubTree(root);
}

BST::node* BST::createLeaf (string a)
{
    node* n = new node;
    n->key = a;
    n->left = NULL;
    n->right = NULL;
    n->value = 1;
    n->height = 1;
    return n;
}

void BST::addLeaf (string a)
{
    addLeafPrivate(a,root);
}

void BST::addLeafPrivate (string s, node* ptr)
{
    if (root == NULL) {
        root = createLeaf(s);
        return;
    }
    int val = s.compare(ptr->key);
    if (val<0) {
        if (ptr->left != NULL)
            addLeafPrivate(s, ptr->left);
        else {
            ptr->left = createLeaf(s);
            return;
        }
    }
    else if (val>0) {
        if (ptr->right != NULL)
            addLeafPrivate(s, ptr->right);
        else {
            ptr->right = createLeaf(s);
            return;
        }
    }
    else
        ptr->value++;
}

void BST::printInorder ()
{
    if (root!=NULL)
        printIn(root);
    else
        cout << "Tree is empty!" << endl;
}

void BST::printIn (node* ptr)
{
    if (ptr->left==NULL) {
        cout << ptr->key << " ";
        if (ptr->right!=NULL)
            printIn(ptr->right);
        if (ptr==root)
            cout<< endl;
        return;
    }
    else {
        printIn(ptr->left);
        cout << ptr->key << " ";
        if (ptr->right!=NULL)
            printIn(ptr->right);
    }
    if (ptr==root)
        cout<< endl;

}

void BST::printPostorder ()
{
    if (root!=NULL)
        printPost(root);
    else
        cout << "Tree is empty!" << endl;
}

void BST::printPost (node* ptr)
{
    if (ptr->left==NULL) {
        if (ptr->right!=NULL)
            printPost(ptr->right);
        cout << ptr->key << " ";
        if (ptr==root)
            cout<< endl;
        return;
    }
    else {
        printPost(ptr->left);
        printPost(ptr->right);
        cout << ptr->key << " ";
    }
    if (ptr==root)
        cout<< endl;
}

void BST::printPreorder ()
{
    if (root!=NULL)
        printPre(root);
    else
        cout << "Tree is empty!" << endl;
}

void BST::printPre (node* ptr)
{
    cout << ptr->key << " ";
    if (ptr->left==NULL) {
        if (ptr->right!=NULL)
            printPre(ptr->right);
        if (ptr==root)
            cout<< endl;
        return;
    }
    else {
        printPre(ptr->left);
        printPre(ptr->right);

    }
    if (ptr==root)
        cout<< endl;
}

BST::node* BST::findNode (string a, node* ptr)
{
    if (ptr->key==a)
        return ptr;
    else if (ptr->key.compare(a)>0) {
        if (ptr->left!=NULL)
            return findNode(a,ptr->left);
        else
            return NULL;
    }
    else {
        if (ptr->right!=NULL)
            return findNode(a,ptr->right);
        else
            return NULL;
    }

}

void BST::findNode (string a)
{
    int c;
    auto start = high_resolution_clock::now();

    if (root==NULL)
        c = -1;
    node* b = findNode(a,root);
    if (b!=NULL)
        c = b->value;
    else
        c = 0;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    print(c,duration.count());
}

void BST::print (int c, long long int d)
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
        cout << "The element: "<< c << " has appeared 1 time in Binary Search Tree." << endl;
        cout << "Duration of search in Binary Search Tree equals " << d << " nanoseconds.\n" << endl;
        return;
    }
    else {
        cout << "The element: "<< c << " has appeared " << c << " times in Binary Search Tree." << endl;
        cout << "Duration of search in Binary Search Tree equals " << d << " nanoseconds.\n" << endl;
        return;
    }
}

BST::node* BST::findBigNode (node* ptr)
{
    if (ptr->right->left==NULL)
        return ptr;
    return findBig (ptr->right);
}

BST::node* BST::findBig (node* ptr)
{
    if (ptr->left->left==NULL)
        return ptr;
    else
        return findBig (ptr->left);
}

BST::node* BST::findSmallNode (node* ptr)
{
    if (ptr->left->right==NULL)
        return ptr;
    return findSmall (ptr->left);
}

BST::node* BST::findSmall (node* ptr)
{
    if (ptr->right->right==NULL)
        return ptr;
    else
        return findSmall(ptr->right);
}

void BST::deleteNode (string a)
{
   deleteNode(a,root);
}

void BST::deleteNode (string a, node* ptr)
{
   if (root!=NULL) {
        if (root->key==a)
            removeNode (root);
        else {
            if (ptr->key.compare(a)>0) {
                if (ptr->left!=NULL && ptr->left->key!=a){
                    deleteNode(a,ptr->left);
                    return;
                }
                else if (ptr->left!=NULL && ptr->left->key==a){
                    removeNode (ptr, ptr->left, false);
                    return;
                }
                else {
                    cout << "Element does not exist." << endl;
                    return;
                }
            }
            if (ptr->key.compare(a)<0) {
                if (ptr->right!=NULL && ptr->right->key!=a){
                    deleteNode(a,ptr->right);
                    return;
                }
                else if (ptr->right!=NULL && ptr->right->key==a){
                    removeNode (ptr, ptr->right, true);
                    return;
                }
                else {
                    cout << "Element does not exist." << endl;
                    return;
                }
            }
        }
   }
   else {
    cout << "The tree is empty." << endl;
    return;
   }
}

void BST::removeNode (node* father, node* ptr, bool a)
{
    int i;
    if (ptr->left==NULL && ptr->right==NULL)
        i=0;
    else if (ptr->left!=NULL && ptr->right!=NULL)
        i=2;
    else
        i=1;
    switch (i) {
        case 0:
            if (a) {
                father->right = NULL;
            }
            else
                father->left = NULL;
            break;
        case 1:
            if (a) {
                if (ptr->left!=NULL)
                    father->right = ptr->left;
                else
                    father->right = ptr->right;
            }
            else {
                if (ptr->left!=NULL)
                    father->left = ptr->left;
                else
                    father->left = ptr->right;
            }
            break;
        case 2:
            node* temp = findBigNode(ptr);
            if (temp==ptr) {
                ptr->key = temp->right->key;
                ptr->value = temp->right->value;
                if(temp->right->right!=NULL)
                    temp->right = temp->right->right;
                else
                    temp->right=NULL;
                break;
            }
            ptr->key = temp->left->key;
            ptr->value = temp->left->value;
            if(temp->left->right!=NULL)
                temp->left = temp->left->right;
            else
                temp->left=NULL;
            break;
    }
}

void BST::removeNode (node* ptr)
{
    if (ptr->left==NULL && ptr->right==NULL) {
        root = NULL;
        return;
    }
    if (root->right!=NULL) {
        node* temp = findBigNode(ptr);
        if (temp==ptr) {
            ptr->key = temp->right->key;
            ptr->value = temp->right->value;
            if(temp->right->right!=NULL)
                temp->right = temp->right->right;
            else
                temp->right=NULL;
            return;
        }
        ptr->key = temp->left->key;
        ptr->value = temp->left->value;
        if(temp->left->right!=NULL)
            temp->left = temp->left->right;
        else
            temp->left=NULL;
        return;
    }
    else if (root->left!=NULL) {
        node* temp = findSmallNode(ptr);
        if (temp==ptr) {
            ptr->key = temp->left->key;
            ptr->value = temp->left->value;
            if(temp->left->left!=NULL)
                temp->left = temp->left->left;
            else
                temp->left=NULL;
            return;
        }
        ptr->key = temp->right->key;
        ptr->value = temp->right->value;
        if(temp->right->left!=NULL)
            temp->right = temp->right->left;
        else
            temp->right=NULL;
        return;
    }

}

void BST::removeSubTree (node* ptr)
{
    if (ptr!=NULL) {
        if (ptr->left!=NULL)
            removeSubTree(ptr->left);
        if (ptr->right!=NULL)
            removeSubTree(ptr->right);
        //cout << "deleting element: " << ptr->key << endl;
        delete ptr;
    }
    else {
        cout << "Tree was empty." << endl;
        return;
    }
}
