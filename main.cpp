#include <iostream>
#include <vector>
#include "BPlusTree.h"
using namespace std;

int main() {
    cout << "Start..."<< endl;

    // ********** TESTING **********
    BPlusTree test(4);
    test.insert(1, "1");
    test.insert(23, "23");
    test.insert(98, "98");
    test.insert(3, "3");
    test.insert(15, "15");
    test.insert(5, "5");
    test.insert(10, "10");
    test.insert(34, "34");
    test.insert(47, "47");
    test.insert(11, "11");
    test.insert(87, "87");
    test.insert(44, "44");
    test.insert(27, "27");
    test.insert(56, "56");
    test.insert(17, "17");
    test.insert(102, "102");
    test.insert(31, "31");
    test.insert(99, "99");
    test.insert(90, "90");
    test.insert(40, "40");
    test.insert(20, "20");
    test.insert(21, "21");
    test.insert(22, "22");
    test.insert(18, "18");
    test.printKeys();
    // test.printValues();
    cout << endl;

    cout << " ****** REMOVAL (unit tests) ******" << endl;

    // // TEST: redistr with right leaf
    // test.remove(5);
    // test.remove(3);
    // test.printKeys();

    // // TEST: redistr with left leaf
    // test.remove(17);
    // test.remove(20);
    // test.printKeys();

    // // TEST: coalesce with left leaf AND coalesce with right interior
    // test.remove(11);
    // test.remove(15);
    // test.remove(10);
    // test.printKeys();
    // test.remove(17);
    // test.printKeys();

    // // TEST: coalesce with right leaf AND coalesce with left interior
    // test.remove(47);
    // test.remove(56);
    // test.printKeys();
    // test.remove(87);
    // test.printKeys();
    // test.printValues();

    // // TEST: redistr with right interior
    // test.insert(32, "32");
    // test.insert(33, "33");
    // test.remove(1);
    // test.remove(3);
    // test.printKeys();
    // test.remove(10);
    // test.printKeys();

    // // TEST: redistr with left interior
    // test.insert(32, "32");
    // test.insert(33, "33");
    // test.remove(102);
    // test.printKeys();
    // test.remove(98);
    // test.printKeys();

    // // TEST: remove all
    // test.remove(10);
    // test.remove(1);
    // test.remove(23);
    // test.remove(98);
    // test.remove(3);
    // test.remove(15);
    // test.remove(5);
    // test.remove(34);
    // test.remove(47);
    // test.remove(11);
    // test.remove(87);
    // test.remove(44);
    // test.remove(27);
    // test.remove(56);
    // test.remove(17);
    // test.remove(102);
    // test.remove(31);
    // test.remove(99);
    // test.remove(90);
    // test.remove(40);
    // test.remove(20);
    // test.remove(21);
    // test.remove(22);
    // test.remove(18);
    // test.printKeys();
    // test.printValues();
    cout << endl;

    cout << " ****** OTHER TESTS ******" << endl;
    // // TEST: BPlusTree copy constructor and = op
    // BPlusTree testCopy(test);
    // BPlusTree test2(4);
    // test2 = test;
    // test.remove(102); // make sure a deep copy was created in both cases
    // test.printKeys();
    // testCopy.printKeys();
    // test2.printKeys();

    // // TEST: BPTreeNode = op
    // test.testBPTreeNodeOverloadOp();

    return 0;
}