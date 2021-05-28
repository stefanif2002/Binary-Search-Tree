#include <iostream>
#include "BST.h"
#include "AVL_BST.h"
#include <cstdlib>
#include <string>

using namespace std;

int main()
{
    int menu = 1;
    string a;
    BST tree;
    AVL_BST tree1;
    while (menu!=0) {
        cout << "Choose action(0:Exit, 1:Insert, 2:Find Info, 3:Delete, 4:Print In-Order, 5:Print Post-Order, 6:Print Pre-Order): ";
        cin >> menu;
        switch (menu)
        {
        case 0:
            break;
        case 1:
            cin >> a;
            tree.addLeaf(a);
            tree1.root = tree1.addLeafAVL(a);
            cout << "The key " << a << " has been inserted." << endl;
            break;
        case 2:
            cin >> a;
            tree.findNode(a);
            tree1.findNode(a);
            break;
        case 3:
            cin >> a;
            tree1.root = tree1.deleteNodeAVL(a);
            tree.deleteNode(a);
            cout << "The key " << a << " has been deleted." << endl;
            break;
        case 4:
            cout << "Binary Search Tree In-Order output: " << endl;
            tree.printInorder();
            cout << "AVL Binary Search Tree In-Order output: " << endl;
            tree1.printInorder ();
            break;
        case 5:
            cout << "Binary Search Tree Post-Order output: " << endl;
            tree.printPostorder();
            cout << "AVL Binary Search Tree Post-Order output: " << endl;
            tree1.printPostorder ();
            break;
        case 6:
            cout << "Binary Search Tree Pre-Order output: " << endl;
            tree.printPreorder();
            cout << "AVL Binary Search Tree Pre-Order output: " << endl;
            tree1.printPreorder ();
            break;
        }
        //cout<<"ok"<<endl;
        //tree1.printInorder ();
        //cout << tree1.root->key << endl;
    }

    return 0;
}
