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

    tree.printValues();
    cout << "----------------" << endl;

    cout << "\n\n REMOVAL \n\n";

    // TEST CASES FROM LECTURE SLIDES
    // cout << "REMOVE 19" << endl;
    // tree.remove(19);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 45" << endl;
    // tree.remove(45);
    // tree.printKeys();
    // cout << "----------------" << endl;

    cout << "REMOVE 9" << endl;
    tree.remove(9);
    tree.printKeys();
    cout << "----------------" << endl;

    cout << "REMOVE 6" << endl;
    tree.remove(6);
    tree.printKeys();
    cout << "----------------" << endl;

    cout << "REMOVE 8" << endl;
    tree.remove(8);
    tree.printKeys();
    cout << "----------------" << endl;

    tree.printValues();

    // cout << "REMOVE 9" << endl;
    // tree.remove(9);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 6" << endl;
    // tree.remove(6);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 60" << endl;
    // tree.remove(60);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 64" << endl;
    // tree.remove(64);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 97" << endl;
    // tree.remove(97);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 8" << endl;
    // tree.remove(8);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 5" << endl;
    // tree.remove(5);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 2" << endl;
    // tree.remove(2);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 19" << endl;
    // tree.remove(19);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 45" << endl;
    // tree.remove(45);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 11" << endl;
    // tree.remove(11);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 7" << endl;
    // tree.remove(7);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 51" << endl;
    // tree.remove(51);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 39" << endl;
    // tree.remove(39);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 31" << endl;
    // tree.remove(31);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 21" << endl;
    // tree.remove(21);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 23" << endl;
    // tree.remove(23);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // cout << "REMOVE 77" << endl;
    // tree.remove(77);
    // tree.printKeys();
    // cout << "----------------" << endl;

    // tree.printValues();

    return 0;
}