#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BPTreeNode {
    private:
        vector<int> keys;
        int currNumOfKeys;
        BPTreeNode* parent;
        vector<BPTreeNode*> children;
        vector<string> values;
        BPTreeNode* nextLeafNode;
        bool isLeaf;
        friend class BPlusTree;
    public:
        BPTreeNode(int maxNumOfKeys);
        BPTreeNode(const BPTreeNode& node);
        BPTreeNode& operator = (const BPTreeNode& node);
        ~BPTreeNode();
};
