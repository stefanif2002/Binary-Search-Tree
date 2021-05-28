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
    /* We compare the heights of the 2 given nodes
    and we return the greater height. */

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
    /* We perform a right rotate
    by setting at the position of the left child of the given node (node y -> left child)
    the right child of it's current left child (node y -> left child = node y -> left child -> right child)
    and then setting at the position of the right child of the current left child of the given node
    the given node itself (node y -> left child -> right child = node y).
    Finally we return the the left child of the given node (node y -> left child).

    Visualization:

                y                x
               / \              / \
              V   V            V   V
              x   w     =>     l   y
             / \                  / \
            V   V                V   V
            l   z                z   w
    */

    node* x = y->left;
    node* z = x->right;

    x->right = y;
    y->left = z;

    y->height = 1 + maxHeight(y->left,y->right);
    x->height = 1 + maxHeight(x->left,x->right);

    return x;
}

BST::node* AVL_BST::leftRotate(node* x)
{
    /* We perform a left rotate
    by setting at the position of the right child of the given node (node x -> right child)
    the left child of it's current right child (node x -> right child = node x -> right child -> left child)
    and then setting at the position of the left child of the current right child of the given node,
    the given node itself (node x -> right child -> left child = node x).
    Finally we return the the right child of the given node (node x -> right child).

    Visualization:

                x                y
               / \              / \
              V   V            V   V
              w   y     =>     x   r
                 / \          / \
                V   V        V   V
                z   r        w   z
    */

    node* y = x->right;
    node* z = y->left;

    y->left = x;
    x->right = z;

    x->height = 1 + maxHeight(x->left,x->right);
    y->height = 1 + maxHeight(y->left,y->right);

    return y;
}

BST::node* AVL_BST::addLeafAVL (string a)
{
    node* ptr = addLeafPrivateAVL (a, root);
    return ptr;
}

BST::node* AVL_BST::addLeafPrivateAVL (string s, node* ptr)
{
    /* Step 1: We execute the BST version of addLeafPrivate(). */

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

    /* We update height of this node. */

    ptr->height = 1 + maxHeight(ptr->left,ptr->right);

    /* Step 2: We find the difference between the heights of the right and left node.
    If the absolute value of the difference is greater than 1
    then we rotate the nodes so that the tree becomes balanced. */

    int balance = isBalanced(ptr);

    // If this node becomes unbalanced, then there are 4 cases.

    // Left Left Case
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
    return ptr;
}

BST::node* AVL_BST::deleteNodeAVL (string a)
{
    return deleteNodeAVL(a,root);
}

BST::node* AVL_BST::deleteNodeAVL (string a, node* ptr)
{
    /* Step 1: We execute the BST version of deleteNode(). */

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

   /* We work similarly with the addLeafPrivateAVL()
   so that we can re-balance the tree if it becomes unbalanced. */

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
    /* Returns the difference between the heights of the right and the left children of the node. */

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
