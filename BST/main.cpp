#include <iostream>
#include "BST.h"
#include "AVL_BST.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

string clearStrBST (string s,BST* tree);
string clearStrAVL_BST (string a, AVL_BST* tree);
BST insertBST ();
AVL_BST insertAVL_BST ();
void menu(BST tree, AVL_BST tree1);

int main()
{
    /* The main function which inserts the data from the file
    and saves them into the structures.
    Afterwards it passes the control to the menu function. */

    BST tree;
    AVL_BST tree1;
    int n =0;


    ifstream myfile1("example.txt");
    string a;
    if (myfile1.is_open())
    {
        while (!myfile1.eof() && n<1000)
        {
            getline(myfile1,a,' ');
            a=clearStrAVL_BST(a,&tree1);
            cout<< n +1 << " " << a << endl;
            tree1.root = tree1.addLeafAVL(a);
            n++;
        }
    }
    else {
        cout << "Unable to open file.";
        exit(-1);
    }
    myfile1.close();

    n=0;

    ifstream myfile("example.txt");
    if (myfile.is_open())
    {
        while (!myfile.eof() && n<1000)
        {
            getline(myfile,a,' ');
            a=clearStrBST(a,&tree);
            cout<< n +1 << " " << a << endl;
            tree.addLeaf(a);
            //
            n++;
        }
    }
    else {
        cout << "Unable to open file.";
        exit(-1);
    }
    myfile.close();

    menu(tree,tree1);
    return 0;
}

void menu(BST tree, AVL_BST tree1)
{
    /* Function that creates a user friendly menu
    so that the saved structures can easily controlled. */

    int menu = 1;
    string a;
    while (menu!=0) {
        cout << "Choose action(0:Exit, 1:Insert, 2:Find Info, 3:Delete, 4:Print In-Order, 5:Print Post-Order, 6:Print Pre-Order): ";
        cin >> menu;
        switch (menu)
        {
        case 0:
            cout << "Good bye!" << endl;
            exit(0);
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
    }
}

string clearStrBST (string a, BST* tree)
{
    /* Erases the extra characters from the string ex: . , ( ) ? : " ect
    and deletes the new line characters */

    string a1;
    size_t i;
    char c = a[a.length()-1];
    a.erase(remove(a.begin(), a.end(), ','), a.end());
    a.erase(remove(a.begin(), a.end(), '('), a.end());
    a.erase(remove(a.begin(), a.end(), ')'), a.end());
    a.erase(remove(a.begin(), a.end(), '?'), a.end());
    a.erase(remove(a.begin(), a.end(), ':'), a.end());
    a.erase(remove(a.begin(), a.end(), '"'), a.end());
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    for (int i=1; i<(int) a.length()-1; i++)
    {

        /* If there is a second string to be saved it save it. */

        c = a[i];
        if (c == '-' || c == '_' || c=='[' || c==']' || c=='.') {
            a1 = a.substr(i+1,a.length()-1);
            a = a.substr(0,i);
            a1.erase(remove(a1.begin(), a1.end(), '\n'), a1.end());
            a1.erase(remove(a.begin(), a.end(), '.'), a.end());
            a1.erase(remove(a.begin(), a.end(), '['), a.end());
            a1.erase(remove(a.begin(), a.end(), ']'), a.end());
            tree->addLeaf(a1);
        }
    }
    i = a.find("\n");
    if (i!=string::npos && (int)i!= (int)a.length()-2 && (int)i!=0) {

        /* If there is a second string to be saved it save it. */

        a1 = a.substr((int)i+1,a.length()-1);
        a = a.substr(0,(int)i);
        a1.erase(remove(a1.begin(), a1.end(), '\n'), a1.end());
        a1.erase(remove(a.begin(), a.end(), '.'), a.end());
        a1.erase(remove(a.begin(), a.end(), '['), a.end());
        a1.erase(remove(a.begin(), a.end(), ']'), a.end());
        tree->addLeaf(a1);
    }
    a.erase(remove(a.begin(), a.end(), '\n'), a.end());
    a.erase(remove(a.begin(), a.end(), '.'), a.end());
    a.erase(remove(a.begin(), a.end(), '['), a.end());
    a.erase(remove(a.begin(), a.end(), ']'), a.end());
    a.erase(remove(a.begin(), a.end(), '-'), a.end());
    a.erase(remove(a.begin(), a.end(), '_'), a.end());
    a.erase(remove(a.begin(), a.end(), ';'), a.end());
    a.erase(remove(a.begin(), a.end(), '!'), a.end());
    return a;
}

string clearStrAVL_BST (string a, AVL_BST* tree)
{
    /* Does the same thing with the clearStrBST()
    but if there is a second string to be saved,
    it saves it as an AVL_BST leaf and not as a BST node. */

    string a1;
    size_t i;
    char c = a[a.length()-1];
    a.erase(remove(a.begin(), a.end(), ','), a.end());
    a.erase(remove(a.begin(), a.end(), '('), a.end());
    a.erase(remove(a.begin(), a.end(), ')'), a.end());
    a.erase(remove(a.begin(), a.end(), '?'), a.end());
    a.erase(remove(a.begin(), a.end(), ':'), a.end());
    a.erase(remove(a.begin(), a.end(), '"'), a.end());
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    for (int i=1; i<(int) a.length()-1; i++)
    {

        /* If there is a second string to be saved it save it. */

        c = a[i];
        if (c == '-' || c == '_' || c=='[' || c==']' || c=='.') {
            a1 = a.substr(i+1,a.length()-1);
            a = a.substr(0,i);
            a1.erase(remove(a1.begin(), a1.end(), '\n'), a1.end());
            a1.erase(remove(a.begin(), a.end(), '.'), a.end());
            a1.erase(remove(a.begin(), a.end(), '['), a.end());
            a1.erase(remove(a.begin(), a.end(), ']'), a.end());
            tree->root = tree->addLeafAVL(a1);
        }
    }
    i = a.find("\n");
    if (i!=string::npos && (int)i!= (int)a.length()-2 && (int)i!=0) {

        /* If there is a second string to be saved it save it. */

        a1 = a.substr((int)i+1,a.length()-1);
        a = a.substr(0,(int)i);
        a1.erase(remove(a1.begin(), a1.end(), '\n'), a1.end());
        a1.erase(remove(a.begin(), a.end(), '.'), a.end());
        a1.erase(remove(a.begin(), a.end(), '['), a.end());
        a1.erase(remove(a.begin(), a.end(), ']'), a.end());
        tree->root = tree->addLeafAVL(a1);
    }
    a.erase(remove(a.begin(), a.end(), '\n'), a.end());
    a.erase(remove(a.begin(), a.end(), '.'), a.end());
    a.erase(remove(a.begin(), a.end(), '['), a.end());
    a.erase(remove(a.begin(), a.end(), ']'), a.end());
    return a;
}

