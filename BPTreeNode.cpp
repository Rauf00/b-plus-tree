#include "BPTreeNode.h"

BPTreeNode::BPTreeNode(int maxNumOfKeys) {
    vector<int> keysVector(maxNumOfKeys);
    vector<BPTreeNode*> childrenVector(maxNumOfKeys + 1, NULL);
    vector<string> valuesVector(maxNumOfKeys);
    keys = keysVector;
    children = childrenVector;
    values = valuesVector;
    parent = NULL;
    isLeaf = false;
    nextLeafNode = NULL;
    currNumOfKeys = 0;
}

BPTreeNode::BPTreeNode(const BPTreeNode& node) {
    keys = node.keys;
    children = node.children;
    values = node.values;
    parent = node.parent;
    isLeaf = node.isLeaf;
    nextLeafNode = node.nextLeafNode;
    currNumOfKeys = node.currNumOfKeys;
}

BPTreeNode& BPTreeNode::operator = (const BPTreeNode& node) { 
    if(this == &node){
        return *this;
    }
    keys = node.keys;
    children = node.children;
    values = node.values;
    parent = node.parent;
    isLeaf = node.isLeaf;
    nextLeafNode = node.nextLeafNode;
    currNumOfKeys = node.currNumOfKeys;
    return *this;
}

BPTreeNode::~BPTreeNode() {
    keys.clear();
    children.clear();
    values.clear();
}
