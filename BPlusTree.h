#pragma once
#include <string>
#include "BPTreeNode.h"
using namespace std;

class BPlusTree {
    private:
        BPTreeNode* root;
        int maxNumOfKeys;
        void printKeysHelper(BPTreeNode* node);
        void printValuesHelper(BPTreeNode* node);
        BPTreeNode* findLeaf(int key, bool rangeFlag);
        bool insertToLeafNode(BPTreeNode* node, int key, string* value);
        BPTreeNode* getLeftBottomLeaf(BPTreeNode* root);
        bool insertToParent(BPTreeNode* node, BPTreeNode* child, int key);
        bool insertToParentNode(BPTreeNode* node, int key, BPTreeNode* value);
        void printChildrenFirst(BPTreeNode* node);
        BPTreeNode* copyLeafToTemp(BPTreeNode* leaf);
        bool distributeValuesBetweenNode(BPTreeNode* tmpNode, BPTreeNode* node1, BPTreeNode* node2);
    public:
        BPlusTree();
        BPlusTree(int maxNumOfKeys);
        bool insert(int, string);
        bool remove(int);
        string find(int);
        void printKeys();
        void printValues();
};  
