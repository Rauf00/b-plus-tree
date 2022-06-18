#include <iostream>
#include <vector>
#include "BPlusTree.h"
using namespace std;

int main() {
    cout << "Start..."<< endl;
    
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

    tree.insert(7, "seven");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(31, "thirty-one");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(45, "forty five");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(51, "fifty-one");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(60, "sixty");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(39, "thirty-nine");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(97, "ninty-seven");
    tree.printKeys();
    cout << "----------------" << endl;

    tree.insert(77, "seventy-seven");
    tree.printKeys();
    cout << "----------------" << endl;

    // tree.printValues();
    // cout << "----------------" << endl;

    tree.remove(19);
    tree.printKeys();
    cout << "----------------" << endl;

    // tree.remove(100);
    // tree.printKeys();
    // cout << "----------------" << endl;

    tree.remove(45);
    tree.printKeys();
    cout << "----------------" << endl;

    return 0;
}