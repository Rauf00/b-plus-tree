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

BPlusTree::BPlusTree(const BPlusTree& tree) {
    root = copyTreeHelper(tree.root);
    maxNumOfKeys = tree.maxNumOfKeys;
}

BPTreeNode* BPlusTree::copyTreeHelper(BPTreeNode* root) {
    if( root == NULL){
		return NULL;
	}
	BPTreeNode *newNode = new BPTreeNode(*root);
	for( int i = 0; i <= root->currNumOfKeys + 1; i++){
		newNode->children[i] = copyTreeHelper(root->children[i]);
	}
	return newNode;
}

BPlusTree& BPlusTree::operator = (const BPlusTree& tree) {
    if(this != &tree){
		deleteTree(root);
		if(tree.root == NULL){
			root = NULL;
			return *this;
		}
		else{
			root = copyTreeHelper(tree.root);
		}
	}
	return *this;
}

// void BPlusTree::testBPTreeNodeOverloadOp() {
//     BPTreeNode node1(3);
//     BPTreeNode node2(3);
//     cout << node1.currNumOfKeys << endl;
//     cout << node2.currNumOfKeys << endl;
//     node1.currNumOfKeys = 2;
//     node2 = node1;
//     cout << node1.currNumOfKeys << endl;
//     cout << node2.currNumOfKeys << endl;
// }

BPlusTree::~BPlusTree() {
    deleteTree(root);
}

void BPlusTree::deleteTree(BPTreeNode* root) {
    if(root == NULL) {
        return;
    }
    queue <BPTreeNode*> que;
    BPTreeNode* parent;
    que.push(root); //insert the root at first
    while(!que.empty()){
        int currLen = que.size();
        while (currLen > 0){
            parent = que.front(); //get the element from the front end
            for(int i = 0; i < parent->currNumOfKeys + 1; i++) {
                if(parent->children.at(i) != NULL) { //When left child is present, insert into queue
                    que.push(parent->children.at(i));
                }
            }
            delete parent;
            que.pop(); //remove the item from queue
            currLen--;
        }
    }
}

bool BPlusTree::insertToLeafNode(BPTreeNode* node, int key, string value) {
    int i = 0; 
    // find key index where to insert
    while (i < (int) node->keys.size() && key > node->keys.at(i)){
        i++;
    }
    // if reached the end, insert to the end
    if (i == (int) node->keys.size()) { 
        node->keys.at(node->currNumOfKeys) = key;
        node->values.at(node->currNumOfKeys) = value;
        node->currNumOfKeys += 1;
    } else {
        // else, move other keys to the right and insert
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

bool BPlusTree::insertToInteriorNode(BPTreeNode* node, int key, BPTreeNode* child) {
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
    child->parent = node;
    return true;
}

BPTreeNode* BPlusTree::copyInteriorToTemp(BPTreeNode* tmpNode, BPTreeNode* node) {
    for(int i = 0; i < node->currNumOfKeys; i++) {
        tmpNode->keys.at(i) = node->keys.at(i);
        node->keys.at(i) = 0;
        tmpNode->currNumOfKeys++;
    }
    for(int i = 0; i < node->currNumOfKeys + 1; i++) {
        tmpNode->children.at(i) = node->children.at(i);
        node->children.at(i) = NULL;
    }
    node->currNumOfKeys = 0;
    return tmpNode;
}

bool BPlusTree::distributeChildrenBetweenNodes(BPTreeNode* tmpNode, BPTreeNode* node1, BPTreeNode* node2) {
    // int middle = (tmpNode->currNumOfKeys % 2 == 0) ? (tmpNode->currNumOfKeys / 2) : (tmpNode->currNumOfKeys / 2 + 1);
    int middle = (tmpNode->currNumOfKeys / 2);
    // move first half of tmpNode to node1
    for (int i = 0; i < middle ; i++) {
        node1->keys.at(i) = tmpNode->keys.at(i);
        node1->currNumOfKeys++;
    }
    for (int i = 0; i < middle + 1 ; i++) {
        node1->children.at(i) = tmpNode->children.at(i);
        tmpNode->children.at(i)->parent = node1;
    }
    // move second half of tmpNode to node2
    int j = 0;
    for (int i = middle + 1; i < tmpNode->currNumOfKeys ; i++) {
        node2->keys.at(j) = tmpNode->keys.at(i);
        node2->currNumOfKeys++;
        j++;
    }
    j = 0;
    for (int i = middle + 1; i < tmpNode->currNumOfKeys + 1; i++) {
        node2->children.at(j) = tmpNode->children.at(i);
        tmpNode->children.at(i)->parent = node2;
        j++;
    }
    return true;
}

bool BPlusTree::insertToParent(BPTreeNode* parent, BPTreeNode* child, int key){
    // if parent is not full
    if(parent->currNumOfKeys != maxNumOfKeys) {
        child->parent = parent;
        insertToInteriorNode(parent, key, child);
    } 
    // if parent is full
    else {
         // create a new node with the last 1⁄2 of the values
        BPTreeNode* newNode = new BPTreeNode(maxNumOfKeys);
        // copy data from orig node to temp
        BPTreeNode* tmpNode = new BPTreeNode(maxNumOfKeys + 1);
        tmpNode = copyInteriorToTemp(tmpNode, parent);
        // insert new value to temp
        insertToInteriorNode(tmpNode, key, child);
        // distribute values from temp between orig and new node
        distributeChildrenBetweenNodes(tmpNode, parent, newNode);

        // int middle = (tmpNode->currNumOfKeys % 2 == 0) ? (tmpNode->currNumOfKeys / 2) : (tmpNode->currNumOfKeys / 2 + 1);
        int middle = (tmpNode->currNumOfKeys / 2);
        // create new root
        if (parent->parent == NULL) {
            BPTreeNode* newRoot = new BPTreeNode(maxNumOfKeys);
            // make the middle value the new root
            newRoot->keys.at(0) = tmpNode->keys.at(middle);
            newRoot->children.at(0) = parent;
            newRoot->children.at(1) = newNode;
            newRoot->currNumOfKeys++;
            parent->parent = newRoot;
            newNode->parent = newRoot;
            root = newRoot;
        }
        else {
            insertToParent(parent->parent, newNode, tmpNode->keys.at(middle));
        }
        delete tmpNode;
    }
    return true;
}

BPTreeNode* BPlusTree::copyLeafToTemp(BPTreeNode* tmpNode, BPTreeNode* leaf) {
    // copy data from orig node to temp
    for(int i = 0; i < leaf->currNumOfKeys; i++) {
        tmpNode->keys.at(i) = leaf->keys.at(i);
        tmpNode->values.at(i) = leaf->values.at(i);
        leaf->values.at(i) = "";
        leaf->keys.at(i) = 0;
        tmpNode->currNumOfKeys++;
    }
    leaf->currNumOfKeys = 0;
    return tmpNode;
}

bool BPlusTree::distributeValuesBetweenNodes(BPTreeNode* tmpNode, BPTreeNode* node1, BPTreeNode* node2, bool adjustNextPointers) {
    int middle = (tmpNode->currNumOfKeys % 2 == 0) ? (tmpNode->currNumOfKeys / 2) : (tmpNode->currNumOfKeys / 2 + 1);
    for (int i = 0; i < middle ; i++) {
        node1->keys.at(i) = tmpNode->keys.at(i);
        node1->values.at(i) = tmpNode->values.at(i);
        node1->currNumOfKeys++;
    }
    int j = 0;
    for (int i = middle; i < tmpNode->currNumOfKeys ; i++) {
        node2->keys.at(j) = tmpNode->keys.at(i);
        node2->values.at(j) = tmpNode->values.at(i);
        node2->currNumOfKeys++;
        j++;
    }
    if(adjustNextPointers) {
        node2->nextLeafNode = node1->nextLeafNode;
        node1->nextLeafNode = node2;
    }
    return true;
}

bool BPlusTree::insert(int key, string value){
    // if tree is empty, init root
    if(root == NULL) {
        root = new BPTreeNode(maxNumOfKeys);
        root->keys.at(0) = key;
        root->values.at(0) = value;
        root->currNumOfKeys += 1;
        root->isLeaf = true;
    } else {
        // find appropriate leaf 
        BPTreeNode* curr = findLeaf(key, true);

        // if key is a duplicate, return false
        if(count(curr->keys.begin(), curr->keys.end(), key)){
            return false;
        }

        // if leaf is not full
        if (curr->currNumOfKeys < maxNumOfKeys) {
            insertToLeafNode(curr, key, value); 
        } 
        // if leaf is full
        else {
            // create a new node with the last 1⁄2 of the values
            BPTreeNode* newNode = new BPTreeNode(maxNumOfKeys);
            newNode->isLeaf = true;
            // copy curr leaf to temp
            BPTreeNode* tmpNode = new BPTreeNode(maxNumOfKeys + 1);
            tmpNode = copyLeafToTemp(tmpNode, curr);
            // insert new value to temp
            insertToLeafNode(tmpNode, key, value);
            // distribute values from temp between orig and new node
            distributeValuesBetweenNodes(tmpNode, curr, newNode, true);
            delete tmpNode;
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


// ***************** REMOVAL *****************

bool BPlusTree::removeFromParent(BPTreeNode* child, BPTreeNode* parent, int childIndex) {
    if(parent == root && parent->currNumOfKeys == 1) {
        if(child == parent->children.at(0)){
            root = parent->children.at(1);
            root->parent = NULL;
            delete parent;
            return true;
        } 
        if(child == parent->children.at(1)){
            root = parent->children.at(0);
            root->parent = NULL;
            delete parent;
            return true;
        } 
    }
    
    BPTreeNode* curr = parent;
    
    // remove child from curr using its index
    for(int i = childIndex; i < curr->currNumOfKeys + 1; i++) {
        curr->children.at(i) = curr->children.at(i + 1);
    }
    for(int i = childIndex - 1; i < curr->currNumOfKeys; i++) {
        if (i < 0) {
            continue;
        }
        curr->keys.at(i) = curr->keys.at(i + 1);
    }
    curr->keys.at(curr->currNumOfKeys - 1) = 0;
    curr->children.at(curr->currNumOfKeys) = NULL;
    curr->currNumOfKeys--;
    
    // if current doesnt have enough keys
    if(curr->currNumOfKeys < maxNumOfKeys / 2 && curr != root) {
        BPTreeNode* currParent = curr->parent;
        int i = 0;
        // find the index of the curr in the parent's children vector 
        for(i = 0; i < currParent->currNumOfKeys; i++) {
            if (currParent->children.at(i) == curr) {
                break;
            }
        }

        // if there is a left sibling 
        if (i - 1 >= 0) {
            BPTreeNode* leftSibling = currParent->children.at(i - 1);
            // if left has enough keys to distribute
            if(leftSibling->currNumOfKeys > maxNumOfKeys / 2) {
                // move last item from left sibling to curr and put it at the beginning
                curr->currNumOfKeys++;
                for (int i = curr->currNumOfKeys - 1; i > 0; i--) {
                    curr->keys.at(i) = curr->keys.at(i - 1);
                }
                for (int i = curr->currNumOfKeys; i > 0; i--) {
                    curr->children.at(i) = curr->children.at(i - 1);
                }
                curr->keys.at(0) = leftSibling->keys.at(leftSibling->currNumOfKeys - 1);
                curr->children.at(0) = leftSibling->children.at(leftSibling->currNumOfKeys);
                leftSibling->children.at(leftSibling->currNumOfKeys)->parent = curr;
                // remove last key from left sibling
                leftSibling->keys.at(leftSibling->currNumOfKeys - 1) = 0;
                // remove last child from the left sibling
                leftSibling->children.at(leftSibling->currNumOfKeys) = NULL;
                leftSibling->currNumOfKeys--;
                // rotate the keys among parent and its chidlren
                int temp = currParent->keys.at(currParent->currNumOfKeys - 1);
                currParent->keys.at(currParent->currNumOfKeys - 1) = curr->keys.at(0); 
                curr->keys.at(0) = temp;
                return true;
            }
        }
        
        // if there is a right sibling
        if (i + 1 < currParent->currNumOfKeys + 1) {
            BPTreeNode* rightSibling = currParent->children.at(i + 1);
            // if right has enough keys to distribute
            if(rightSibling->currNumOfKeys > maxNumOfKeys / 2) {
                // move first item from right sibling to curr
                insertToInteriorNode(curr, rightSibling->keys.at(0), rightSibling->children.at(0));
                // remove first key from right sibling
                for (int i = 0; i < rightSibling->currNumOfKeys - 1; i++) {
                    rightSibling->keys.at(i) = rightSibling->keys.at(i + 1);
                }
                rightSibling->keys.at(rightSibling->currNumOfKeys - 1) = 0;
                // remove first child from the right sibling
                for (int i = 0; i < rightSibling->currNumOfKeys; i++) {
                    rightSibling->children.at(i) = rightSibling->children.at(i + 1);
                }
                rightSibling->children.at(rightSibling->currNumOfKeys) = NULL;
                rightSibling->currNumOfKeys--;
                // rotate the keys among parent and its chidlren
                int temp = currParent->keys.at(i);
                currParent->keys.at(i) = curr->keys.at(curr->currNumOfKeys - 1); 
                curr->keys.at(curr->currNumOfKeys - 1) = temp;
                return true;
            }
        }
        
        // if left sibling is not half full
        if (i - 1 >= 0) {
            BPTreeNode* leftSibling = currParent->children.at(i - 1);
            leftSibling->keys.at(leftSibling->currNumOfKeys) = currParent->keys.at(i - 1);
            leftSibling->currNumOfKeys++;
            // move items from curr to leftsibling 
            int leftSibSize = leftSibling->currNumOfKeys;
            for (int  i = 0; i < curr->currNumOfKeys; i++) {
                leftSibling->keys.at(leftSibSize + i) = curr->keys.at(i);
                leftSibling->currNumOfKeys++;
            }
            for (int  i = 0; i < curr->currNumOfKeys + 1; i++) {
                leftSibling->children.at(leftSibSize + i) = curr->children.at(i);
                curr->children.at(i)->parent = leftSibling;
            }
            removeFromParent(curr, currParent, i);
            delete curr;
        }

        // if right sibling is not half full
        if (i + 1 < currParent->currNumOfKeys + 1) {
            BPTreeNode* rightSibling = currParent->children.at(i + 1);
            rightSibling->keys.insert(rightSibling->keys.begin(), currParent->keys.at(i));
            rightSibling->currNumOfKeys++;
            // move items from curr to right sibling
            for (int  i = curr->currNumOfKeys - 1; i >= 0; i--) {
                rightSibling->keys.insert(rightSibling->keys.begin(), curr->keys.at(i));
                rightSibling->currNumOfKeys++;
            }
            for (int  i = curr->currNumOfKeys; i >= 0; i--) {
                rightSibling->children.insert(rightSibling->children.begin(), curr->children.at(i));
                curr->children.at(i)->parent = rightSibling;
            }
            removeFromParent(curr, currParent, i);
            delete curr;
        }
    }
    return true;
}

bool BPlusTree::remove(int key) {
    // find a leaf where key might be located 
    BPTreeNode* curr = findLeaf(key, true);

    // if key is not in curr, key is not in the tree, so return false
    if(count(curr->keys.begin(), curr->keys.end(), key) == 0){
        return false;
    }

    // remove key from the leaf
    for(int i = 0; i < curr->currNumOfKeys; i++) {
        if(curr->keys.at(i) == key) {
            for(int j = i; j < curr->currNumOfKeys - 1; j++) {
                curr->keys.at(j) = curr->keys.at(j + 1);
                curr->values.at(j) = curr->values.at(j + 1);
            }
            curr->currNumOfKeys--;
        }
    }

    // if no items in the root, delete root
    if (curr == root && root->currNumOfKeys == 0) {
        root = NULL;
        delete curr;
        return true;
    } 
    
    int halfNumOfKeys = (maxNumOfKeys % 2 == 0) ? (maxNumOfKeys / 2) : (maxNumOfKeys / 2 + 1);
    
    // if leaf doesnt have enough keys
    if(curr->currNumOfKeys < halfNumOfKeys && curr != root) {
        BPTreeNode* currParent = curr->parent;
        int i = 0;
        // find the index of the curr in its parent's children vector
        for(i = 0; i < currParent->currNumOfKeys; i++) {
            if (currParent->children.at(i) == curr) {
                break;
            }
        }

        // if the index of current is >= than 1, the there is a left sibling 
        if (i >= 1) {
            BPTreeNode* leftSibling = currParent->children.at(i - 1);
            // if left sibling has enough keys to distribute
            if(leftSibling->currNumOfKeys > halfNumOfKeys) {
                // copy left sibling to temp
                BPTreeNode* tmpNode = new BPTreeNode(maxNumOfKeys + 1);
                tmpNode = copyLeafToTemp(tmpNode, leftSibling);
                // insert items from curr to temp
                for(int i = 0; i < curr->currNumOfKeys; i++) {
                    insertToLeafNode(tmpNode, curr->keys.at(i), curr->values.at(i));
                    curr->currNumOfKeys--;
                }
                distributeValuesBetweenNodes(tmpNode, leftSibling, curr, false);
                // replace the removed key by the first key of curr in the parent
                currParent->keys.at(i - 1) = curr->keys.at(0);
                delete tmpNode;
                return true;
            }
        }

        // if there is a right sibling (there are currNumOfKeys + 1 )
        if (i < currParent->currNumOfKeys) {
            BPTreeNode* rightSibling = currParent->children.at(i + 1);
            // if right sibling has enough keys to distribute
            if(rightSibling->currNumOfKeys > halfNumOfKeys) {
                BPTreeNode* tmpNode = new BPTreeNode(maxNumOfKeys + 1);
                tmpNode = copyLeafToTemp(tmpNode, rightSibling);
                for(int i = 0; i < curr->currNumOfKeys; i++) {
                    insertToLeafNode(tmpNode, curr->keys.at(i), curr->values.at(i));
                    curr->currNumOfKeys--;
                }
                distributeValuesBetweenNodes(tmpNode, curr, rightSibling, false);
                // replace the removed key by the first key of right sibling in the parent
                currParent->keys.at(i) = rightSibling->keys.at(0);
                delete tmpNode;
                return true;
            }
        }
        
        // if left sibling is not half full, then coalesce
        if (i >= 1) {
            BPTreeNode* leftSibling = currParent->children.at(i - 1);
            // move keys and values to leftsibling
            for(int i = 0; i < curr->currNumOfKeys; i++) {
                insertToLeafNode(leftSibling, curr->keys.at(i), curr->values.at(i));
            }
            leftSibling->nextLeafNode = curr->nextLeafNode;
            removeFromParent(curr, currParent, i);
            // remove curr node
            delete curr;
            return true;
        }

        // if right sibling is not half full, then coalesce
        if (i < currParent->currNumOfKeys) {
            BPTreeNode* rightSibling = currParent->children.at(i + 1);
            // move keys and values to rightsibling
            for(int i = 0; i < curr->currNumOfKeys; i++) {
                insertToLeafNode(rightSibling, curr->keys.at(i), curr->values.at(i));
            }
            BPTreeNode* prev = root;
            while (prev->children.at(0) != NULL) {
                prev = prev->children.at(0);
            }
            while (prev != curr && prev->nextLeafNode != curr) {
                prev = prev->nextLeafNode;
            }
            prev->nextLeafNode = rightSibling;
            removeFromParent(curr, currParent, i);
            // remove curr node
            delete curr;
            return true;
        }
    }
    return true;
}

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
            } else if(key >= curr->keys.at(curr->currNumOfKeys - 1)) {
                curr = curr->children.at(curr->currNumOfKeys);
            } else {
                int i = 0;
                while(key >= curr->keys.at(i)) {
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
                return leaf->values.at(i);
            }
        }
    }
    return "";
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
    //     cout << "--" << node->parent->keys.at(0) << " ";
    // }
    // if(node->children.at(0)){
    //     printChildrenFirst(node);
    // }
    cout << "] ";
}

void BPlusTree::printChildrenFirst(BPTreeNode* node) {
    cout << "-- [";
    for(int i = 0; i < node->currNumOfKeys + 1; i++) {
        cout << node->children.at(i)->keys.at(0) << " ";
    }
    cout << "] ";
}

void BPlusTree::printKeys() {
    if(root == NULL) {
        cout << "Tree is empty!" <<endl;
        return;
    }
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
        cout << node->values.at(i) << endl;
    }
}

void BPlusTree::printValues() {
    if(root == NULL) {
        cout << "Tree is empty!" <<endl;
        return;
    }
    BPTreeNode* curr = root;
    while (curr->children.at(0) != NULL) {
        curr = curr->children.at(0);
    }
    while(curr != NULL) {
        printValuesHelper(curr);
        curr = curr->nextLeafNode;
    }
}