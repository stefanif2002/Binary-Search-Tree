#ifndef BST_H
#define BST_H
#include <string>
using namespace std;

class BST
{
    protected:
        struct node {               //The structure of a node
            string key;
            node* left;
            node* right;
            int value;
            int height;
        };

        node* createLeaf (string a);                //Function to create and initialize a leaf
        void addLeafPrivate (string a, node* ptr);  //Function to find at which node of the tree the new leaf should be added as child
        void printIn (node* ptr);                   //Function to print the tree In-Order
        void printPost (node* ptr);                 //Function to print the tree Post-Order
        void printPre (node* ptr);                  //Function to print the tree Pre-Order
        node* findNode (string a, node* ptr);       //Function to find and return the node with the given key
        node* findBigNode (node* ptr);              //Function to find and return the node with the biggest value within the given subtree (Part 1)
        node* findBig (node* ptr);                  //Function to find and return the node with the biggest value within the given subtree (Part 2)
        node* findSmallNode (node* ptr);            //Function to find and return the node with the smallest value within the given subtree (Part 1)
        node* findSmall (node* ptr);                //Function to find and return the node with the smallest value within the given subtree (Part 2)
        void deleteNode (string a, node* ptr);      //Function to find the node with the given key and delete it
        void removeNode (node* father, node* ptr, bool a);  //Function to remove the given node
        void removeNode (node* ptr);                //Function to remove the given node (Only when removing the root of the tree)
        void removeSubTree (node* ptr);             //Function to delete a tree
        virtual void print (int c, long long int d, string a);//Function to print the information of the found node (times that the key have been appeared and time that the execution has taken)

    private:

    public:
        BST();
        ~BST();
        node* root;                 //The root of the tree
        void addLeaf (string a);    //Public function to pass the control to the "addLeafPrivate()" function in order to create a leaf with the given key
        void printInorder ();       //Public function to pass the control to the "printIn()" function in order to print the tree In-Order
        void printPostorder ();     //Public function to pass the control to the "printPost()" function in order to print the tree Post-Order
        void printPreorder ();      //Public function to pass the control to the "printPre()" function in order to print the tree Pre-Order
        void findNode (string a);   //Public function to pass the control to the "findNode()" function in order to find the node with the given key
        void deleteNode (string a); //Public function to pass the control to the "deleteNode()" function in order to delete the node with the given key

};

#endif // BST_H
