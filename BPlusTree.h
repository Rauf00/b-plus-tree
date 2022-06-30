#pragma once
#include <string>
#include "BPTreeNode.h"
using namespace std;

class BPlusTree {
    private:
        BPTreeNode* root;
        int maxNumOfKeys;
        BPTreeNode* copyTreeHelper(BPTreeNode* root);
        void deleteTree(BPTreeNode* root);
        BPTreeNode* findLeaf(int key, bool rangeFlag);
        bool insertToLeafNode(BPTreeNode* node, int key, string value);
        bool insertToParent(BPTreeNode* node, BPTreeNode* child, int key);
        bool insertToInteriorNode(BPTreeNode* node, int key, BPTreeNode* value);
        BPTreeNode* copyLeafToTemp(BPTreeNode* tmpNode, BPTreeNode* leaf);
        BPTreeNode* copyInteriorToTemp(BPTreeNode* temp, BPTreeNode* node);
        bool distributeValuesBetweenNodes(BPTreeNode* tmpNode, BPTreeNode* node1, BPTreeNode* node2, bool adjustNextPointers);
        bool distributeChildrenBetweenNodes(BPTreeNode* tmpNode, BPTreeNode* node1, BPTreeNode* node2);
        bool removeFromParent(BPTreeNode* child, BPTreeNode* parent, int childIndex);
        void printKeysHelper(BPTreeNode* node);
        void printValuesHelper(BPTreeNode* node);
        void printChildrenFirst(BPTreeNode* node);
    public:
        BPlusTree();
        BPlusTree(int maxNumOfKeys);
        BPlusTree(const BPlusTree& tree);
        BPlusTree& operator = (const BPlusTree& tree);
        // void testBPTreeNodeOverloadOp();
        ~BPlusTree();
        bool insert(int, string);
        bool remove(int);
        string find(int);
        void printKeys();
        void printValues();
};  
