#include <iostream>
#include <vector>
#include "BPlusTree.h"
using namespace std;

int main() {
    cout << "Start..."<< endl;
    
    // BPTreeNode node = BPTreeNode(vect1, vect2);
    // vector<int> keys = node.getKeys();
    // for(int i=0; i < keys.size(); i++) {
    //     cout << keys.at(i) << endl;
    // }

    BPlusTree tree = BPlusTree(3);
    tree.insert(2, "two");
    tree.printKeys();
    cout << "----------------" << endl;
    tree.insert(21, "twenty-one");
    tree.printKeys();
    cout << "----------------" << endl;
    tree.insert(11, "eleven");
    tree.printKeys();
    cout << "----------------" << endl;
    // cout << tree.find(11) << endl;
    tree.insert(8, "eight");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(64, "sixty-four");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(5, "five");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(23, "twenty-three");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(6, "six");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(19, "nineteen");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(9, "nine");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.printValues();
    cout << "----------------" << endl;

    return 0;
}