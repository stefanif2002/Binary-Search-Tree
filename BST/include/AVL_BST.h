#ifndef AVL_BST_H
#define AVL_BST_H
#include "BST.h"
#include <string>
using namespace std;


class AVL_BST : public BST
{
    public:
        AVL_BST();
        virtual ~AVL_BST();
        node* addLeafAVL (string a);                    //Public function to pass the control to the "addLeafPrivate()" function in order to create a leaf with the given key
        node* deleteNodeAVL (string a);                 //Public function to pass the control to the "deleteNode()" function in order to delete the node with the given key

    protected:

    private:
        node* addLeafPrivateAVL (string a, node* ptr);  //Function to find at which node of the tree the new leaf should be added as child
        int isBalanced (node* ptr);                     //Function to find the difference of the heights of the right and left child of the given node
        int maxHeight (node* ptr1, node* ptr2);         //Function to find and return the node with the bigger height
        node* deleteNodeAVL (string a, node* ptr);      //Function to find the node with the given key and delete it
        node* rightRotate(node* y);                     //Function to perform a right rotate during the self-balancing procedure
        node* leftRotate(node* x);                      //Function to perform a left rotate during the self-balancing procedure
        void print (int c, long long int d);            //Function to print the information of the found node (times that the key have been appeared and time that the execution has taken)
};

#endif // AVL_BST_H
