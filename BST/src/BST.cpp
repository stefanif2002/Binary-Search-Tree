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
    root = NULL;
}

BST::node* BST::createLeaf (string a)
{
    //We try to allocate memory
    //In case we can't we throw exeption

    try {
        node* n = new node;
        n->key = a;
        n->left = NULL;
        n->right = NULL;
        n->value = 1;
        n->height = 1;
        return n;
    }
    catch (...) {
        cout << "Could not allocate memory.";
        exit(-1);
    }
}

void BST::addLeaf (string a)
{
    addLeafPrivate(a,root);
}

void BST::addLeafPrivate (string s, node* ptr)
{
    // Step 1: If we don't have a root we create one.

    if (root == NULL) {
        root = createLeaf(s);
        return;
    }

    /* Step 2: If we have a root, then we find the difference
    between the given key and the key of the current node. */

    int val = s.compare(ptr->key);

    /* Step 3: We choose which path we should take.
    If the difference has value greater than 0
    then the key is greater than the key of the current node
    so we take the right path of the tree,
    if it is equal we increase the value of the current node
    else we take the left path of the tree. */

    if (val<0) {

        /* If the current node has a left child
        then we call the  addLeafPrivate() function for it,
        otherwise we create a node
        and assign it as the left child of the current node. */

        if (ptr->left != NULL)
            addLeafPrivate(s, ptr->left);
        else {
            ptr->left = createLeaf(s);
            return;
        }
    }
    else if (val>0) {

        // We execute the same thing for the case of the right child.

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
    /* We print with the Left-Root-Right principle which means that
    for every node we first print the key of it's left child,
    then the key of the node itself
    and finally the key of the the right child */

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
    /*  We print with the Left-Right-Root principle. */

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
        if (ptr->right!=NULL)
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
    /*  We print with the Root-Left-Right principle. */

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
        if (ptr->right!=NULL)
            printPre(ptr->right);

    }
    if (ptr==root)
        cout<< endl;
}

BST::node* BST::findNode (string a, node* ptr)
{
    /* Step 1: We find the difference
    between the given key and the key of the current node.
    If they are equal then the wanted node has been found. */

    if (ptr->key==a)
        return ptr;

        /* Step 2: Else we choose which path we should take.
    If the difference has value greater than 0
    then the key is greater than the key of the current node
    so we take the right path of the tree,
    if it is equal we increase the value of the current node
    else we take the left path of the tree. */

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
    /* We chrono the time that it takes for the function findNode()
    to find the node with the specified key.  */

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
    print(c,duration.count(),a);
}

void BST::print (int c, long long int d, string a)
{
    /* We print the information about the found key. */

    if (c==-1) {
        cout << "The tree is empty." << endl;
        return;
    }
    else if (c==0) {
        cout << "Element does not exist." << endl;
        return;
    }
    else if (c==1) {
        cout << "The element: "<< a << " has appeared 1 time in Binary Search Tree." << endl;
        cout << "Duration of search in Binary Search Tree equals " << d << " nanoseconds.\n" << endl;
        return;
    }
    else {
        cout << "The element: "<< a << " has appeared " << c << " times in Binary Search Tree." << endl;
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
    /* Step 1: We find the node with given key with the method of comparisons
    (the same with the findNode and addLeafPrivate functions). */

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

                    /* Step 2: After we found it we remove it. */

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
    /* Step 3: We categorize the node.
    There are 3 cases:
        Case 1: The node has no children
        Case 2: The node has 1 child
        Case 3: The node has 2 children */

    int i;
    if (ptr->left==NULL && ptr->right==NULL)
        i=1;
    else if (ptr->left!=NULL && ptr->right!=NULL)
        i=3;
    else
        i=2;

    /* Step 4: We finally remove the node
    according to the category that it belongs */

    switch (i) {
        case 1:
            if (a) {
                father->right = NULL;
            }
            else
                father->left = NULL;
            break;
        case 2:
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
        case 3:
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
    /* If we have to remove the root, then we replace it
    with the node of the left subtree that has the greater value */

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
    /* When we have to destroy the tree
    we remove every node from the left sub tree,
    and then every node from the right subtree.  */

    if (ptr!=NULL) {
        if (ptr->left!=NULL)
            removeSubTree(ptr->left);
        if (ptr->right!=NULL)
            removeSubTree(ptr->right);
        delete ptr;
    }
    else {
        cout << "Tree was empty." << endl;
        return;
    }
}
