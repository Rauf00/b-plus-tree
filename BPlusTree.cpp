#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "BPlusTree.h"
using namespace std;


BPlusTree::BPlusTree() {
    root = NULL;
    maxNumOfKeys = 0;
}

BPlusTree::BPlusTree(int aNumOfKeys) {
    root = NULL;
    maxNumOfKeys = aNumOfKeys;
}

bool BPlusTree::insertToNode(BPTreeNode* node, int key, string* value) {
    int i = 0; 
    while (i < (int) node->keys.size() && key > node->keys.at(i)){
        i++;
    }
    if (i == (int) node->keys.size()) { 
        node->keys.at(node->currNumOfKeys) = key;
        node->values.at(node->currNumOfKeys) = value;
        node->currNumOfKeys += 1;
    } else {
        for(int j = node->currNumOfKeys; j > i; j--){
            node->keys.at(j) = node->keys.at(j - 1);
            node->values.at(j) = node->values.at(j - 1);
        }
        node->keys.at(i) = key;
        node->values.at(i) = value;
        node->currNumOfKeys += 1;
    }
    return true;
}

bool BPlusTree::insertToParentNode(BPTreeNode* node, int key, BPTreeNode* child) {
    int i = 0; 
    while (i < (int) node->keys.size() && key > node->keys.at(i)){
        i++;
    }
    if (i == (int) node->keys.size()) { 
        node->keys.at(node->currNumOfKeys) = key;
        node->children.at(node->currNumOfKeys + 1) = child;
        node->currNumOfKeys += 1;
    } else {
        for(int j = node->currNumOfKeys; j > i; j--){
            node->keys.at(j) = node->keys.at(j - 1);
            node->children.at(j + 1) = node->children.at(j);
        }
        node->keys.at(i) = key;
        node->children.at(i + 1) = child;
        node->currNumOfKeys += 1;
    }
    return true;
}

bool BPlusTree::insertToParent(BPTreeNode* parent, BPTreeNode* child, int key){
    // if parent is not full
    if(parent->currNumOfKeys != maxNumOfKeys) {
        child->parent = parent;
        insertToParentNode(parent, key, child);
    } 
    // if parent is full
    else {
         // create a new node with the last 1⁄2 of the values
        BPTreeNode* newNode = new BPTreeNode(maxNumOfKeys);

        BPTreeNode* tmpNode = new BPTreeNode(maxNumOfKeys + 1);
        // copy data from orig node to temp
        for(int i = 0; i < parent->currNumOfKeys; i++) {
            tmpNode->keys.at(i) = parent->keys.at(i);
            parent->keys.at(i) = 0;
            tmpNode->currNumOfKeys++;
        }
        for(int i = 0; i < parent->currNumOfKeys + 1; i++) {
            tmpNode->children.at(i) = parent->children.at(i);
            parent->children.at(i) = NULL;
        }
        parent->currNumOfKeys = 0;

        // insert new value to temp
        insertToParentNode(tmpNode, key, child);

        // distribute values from temp between orig and new node
        int middle = (tmpNode->currNumOfKeys % 2 == 0) ? (tmpNode->currNumOfKeys / 2) : (tmpNode->currNumOfKeys / 2 + 1);
        for (int i = 0; i < middle ; i++) {
            parent->keys.at(i) = tmpNode->keys.at(i);
            parent->currNumOfKeys++;
        }
        for (int i = 0; i < middle + 1 ; i++) {
            parent->children.at(i) = tmpNode->children.at(i);
            tmpNode->children.at(i)->parent = parent;

        }
        int j = 0;
        for (int i = middle + 1; i < tmpNode->currNumOfKeys ; i++) {
            newNode->keys.at(j) = tmpNode->keys.at(i);
            newNode->currNumOfKeys++;
            j++;
        }
        j = 0;
        for (int i = middle + 1; i < tmpNode->currNumOfKeys + 1; i++) {
            newNode->children.at(j) = tmpNode->children.at(i);
            tmpNode->children.at(i)->parent = newNode;
            j++;
        }

        // create new root
        if (parent->parent == NULL) {
            BPTreeNode* newRoot = new BPTreeNode(maxNumOfKeys);
            // make the middle value the new root
            newRoot->keys.at(0) = tmpNode->keys.at(middle);
            newRoot->currNumOfKeys++;

            newRoot->children.at(0) = parent;
            newRoot->children.at(1) = newNode;
            parent->parent = newRoot;
            newNode->parent = newRoot;
            root = newRoot;
        }
        else {
            insertToParent(parent->parent, newNode, tmpNode->keys.at(middle));
        }
    }
    return true;
}

bool BPlusTree::insert(int key, string value){
    if(root == NULL) {
        root = new BPTreeNode(maxNumOfKeys);
        root->keys.at(0) = key;
        root->values.at(0) = &value;
        root->currNumOfKeys += 1;
        root->isLeaf = true;
    } else {
        // find appropriate leaf 
        BPTreeNode* curr = findLeaf(key, true);
        // if leaf is not full
        if (curr->currNumOfKeys < maxNumOfKeys) {
            insertToNode(curr, key, &value); 
        } 
        // if leaf is full
        else {
            // create a new node with the last 1⁄2 of the values
            BPTreeNode* newNode = new BPTreeNode(maxNumOfKeys);
            newNode->isLeaf = true;

            BPTreeNode* tmpNode = new BPTreeNode(maxNumOfKeys + 1);
            // copy data from orig node to temp
            for(int i = 0; i < curr->currNumOfKeys; i++) {
                tmpNode->keys.at(i) = curr->keys.at(i);
                tmpNode->values.at(i) = curr->values.at(i);
                curr->children.at(i) = 0;
                curr->keys.at(i) = 0;
                tmpNode->currNumOfKeys++;
            }
            curr->currNumOfKeys = 0;

            // insert new value to temp
            insertToNode(tmpNode, key, &value);
            
            // distribute values from temp between orig and new node
            int middle = (tmpNode->currNumOfKeys % 2 == 0) ? (tmpNode->currNumOfKeys / 2) : (tmpNode->currNumOfKeys / 2 + 1);
            for (int i = 0; i < middle ; i++) {
                curr->keys.at(i) = tmpNode->keys.at(i);
                curr->values.at(i) = tmpNode->values.at(i);
                curr->currNumOfKeys++;
            }
            int j = 0;
            for (int i = middle; i < tmpNode->currNumOfKeys ; i++) {
                newNode->keys.at(j) = tmpNode->keys.at(i);
                newNode->values.at(j) = tmpNode->values.at(i);
                newNode->currNumOfKeys++;
                j++;
            }
            newNode->nextLeafNode = curr->nextLeafNode;
            curr->nextLeafNode = newNode;
            
            // create new root
            if (curr->parent == NULL) {
                BPTreeNode* newRoot = new BPTreeNode(maxNumOfKeys);

                newRoot->keys.at(0) = newNode->keys.at(0);
                newRoot->currNumOfKeys++;

                newRoot->children.at(0) = curr;
                newRoot->children.at(1) = newNode;
                curr->parent = newRoot;
                newNode->parent = newRoot;
                root = newRoot;
            }
            else {
                insertToParent(curr->parent, newNode, newNode->keys.at(0));
            }
        }
    }
    return true;
}

bool remove(int);

BPTreeNode* BPlusTree::findLeaf(int key, bool rangeFlag) {
    BPTreeNode* curr = root;
    while (curr != NULL) {
        if (curr->isLeaf) {
            for (int i = 0; i < curr->currNumOfKeys; i++) {
                if(curr->keys.at(i) == key) {
                    return curr;
                }
            }
            break;
        } 
        else {
            if (key < curr->keys.at(0)) {
                curr = curr->children.at(0);
            } else if(key > curr->keys.at(curr->currNumOfKeys - 1)) {
                curr = curr->children.at(curr->currNumOfKeys);
            } else {
                int i = 0;
                while(key > curr->keys.at(i)) {
                    i++;
                }
                curr = curr->children.at(i);
            }
        }
    }
    return rangeFlag ? curr : NULL;
    
}

string BPlusTree::find(int key) {
    BPTreeNode* leaf = findLeaf(key, false);
    if (leaf != NULL) {
        for (int i = 0; i < (int) leaf->keys.size(); i++) {
            if(leaf->keys.at(i) == key) {
                cout << "found at " << i<<endl;
                return *leaf->values.at(i);
            }
        }
    }
    return "Not Found";
}

void BPlusTree::printKeysHelper(BPTreeNode* node) {
    cout << "[";
    for(int i = 0; i < node->currNumOfKeys; i++) {
        cout << node->keys.at(i);
        if (i != node->currNumOfKeys - 1) {
            cout << ",";
        }
    }
    // if (node->parent) {
    //     cout << "--" << node->parent->keys.at(0);
    // }
    cout << "] ";
}

void BPlusTree::printChildrenFirst(BPTreeNode* node) {
    cout << "children: [";
    for(int i = 0; i < node->currNumOfKeys + 1; i++) {
        cout << node->children.at(i)->keys.at(0) << " ";
    }
    cout << "] ";
}

void BPlusTree::printKeys() {
    queue <BPTreeNode*> que;
    BPTreeNode* parent;
    que.push(root); //insert the root at first
    while(!que.empty()){
        int currLen = que.size();
        while (currLen > 0){
            parent = que.front(); //get the element from the front end
            printKeysHelper(parent);
            for(int i = 0; i < parent->currNumOfKeys + 1; i++) {
                if(parent->children.at(i) != NULL) { //When left child is present, insert into queue
                    que.push(parent->children.at(i));
                }
            }
            que.pop(); //remove the item from queue
            currLen--;
        }
        cout << endl;
    }
}

void BPlusTree::printValuesHelper(BPTreeNode* node) {
    for(int i = 0; i < node->currNumOfKeys; i++) {
        cout << *node->values.at(i) << endl;
    }
}

void BPlusTree::printValues() {
    BPTreeNode* curr = root;
    
    while (curr->children.at(0) != NULL) {
        curr = curr->children.at(0);
    }
    while(curr != NULL) {
        printValuesHelper(curr);
        curr = curr->nextLeafNode;
    }
}