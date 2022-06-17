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
        vector<string*> values;
        BPTreeNode* nextLeafNode;
        bool isLeaf;
        friend class BPlusTree;
    public:
        BPTreeNode(int maxNumOfKeys);
        virtual ~BPTreeNode(){};
};



// class BPTreeLeafNode : public BPTreeNode {
//     protected:
//         vector<string*> values;
//     public:
//         BPTreeLeafNode(int maxNumOfKeys);
//         ~BPTreeLeafNode(){};
// };

// class BPTreeInteriorNode : public virtual BPTreeNode {
//     protected:
//         vector<BPTreeNode*> children;
//     public:
//         BPTreeInteriorNode(int maxNumOfKeys);
//         ~BPTreeInteriorNode(){};
// };
