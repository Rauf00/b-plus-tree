#include "BPTreeNode.h"

BPTreeNode::BPTreeNode(int maxNumOfKeys) {
    vector<int> keysVector(maxNumOfKeys);
    vector<BPTreeNode*> childrenVector(maxNumOfKeys + 1, NULL);
    vector<string*> valuesVector(maxNumOfKeys);
    
    keys = keysVector;
    children = childrenVector;
    values = valuesVector;
    parent = NULL;
    isLeaf = false;
    nextLeafNode = NULL;
    currNumOfKeys = 0;
}

// // BPTreeLeafNode class implementation
// BPTreeLeafNode::BPTreeLeafNode(int maxNumOfKeys): BPTreeNode(maxNumOfKeys) {
//     vector<string> valuesVector(maxNumOfKeys + 1);
//     values = valuesVector;
// }

// // BPTreeInteriorNode class implementation
// BPTreeInteriorNode::BPTreeInteriorNode(int maxNumOfKeys): BPTreeNode(maxNumOfKeys) {
//     vector<BPTreeNode*> childrenVector(maxNumOfKeys + 1);
//     children = childrenVector;
// }
