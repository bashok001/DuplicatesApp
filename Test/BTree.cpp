#include "BTree.h"
#include "iostream"


BTree::BTree(){

	root = NULL;

}

void sort(BTreeNode* node, int key){

	int i = node->keys.size() -2;

	while (i >= 0 && node->keys.at(i) > key){

		node->keys.at(i + 1) = node->keys.at(i);
		i--;

	}
	node->keys.at(i + 1) = key;
	
}

BTreeNode* BTree::split(BTreeNode* node){

	int mid = node->keys.size() / 2;
	BTreeNode* parent = node->parent;

	if (node->parent == NULL){

		BTreeNode* childOne = new BTreeNode(), *childTwo = new BTreeNode(), *newNode = new BTreeNode();
		newNode->keys.push_back(node->keys.at(mid));
		newNode->keysSize++;

		node->keys.erase(node->keys.begin() + mid);
		node->keysSize--;

		int size = node->keys.size();

		for (int i = mid; i < size; i++){

			childTwo->keys.push_back(node->keys[mid]);
			childTwo->keysSize++;

			node->keys.erase(node->keys.begin() + mid);
			node->keysSize--;
		}

		childOne = node;
		node = newNode;
		childOne->parent = newNode;
		childTwo->parent = newNode;

		newNode->child.push_back(childOne);
		newNode->childSize++;
		newNode->child.push_back(childTwo);
		newNode->childSize++;

		if (childOne->childSize > 6){

			int size = childOne->childSize;
			for (int i = mid + 1; i < size; i++){

				childTwo->child.push_back(childOne->child[mid + 1]);
				childOne->child[mid + 1]->parent = childTwo;
				childTwo->childSize++;

				childOne->child.erase(childOne->child.begin() + mid + 1);
				childOne->childSize--;
			}

			root = node;
		}
	}
	else{

		int pos = 0;
		int num = node->keys[mid];
		for (pos = 0; pos < parent->keys.size(); pos++){

			if (num < parent->keys[pos])
				break;
		}

		parent->setKey(pos, num);
		parent->keysSize++;
		node->keys.erase(node->keys.begin() + mid);
		node->keysSize--;

		BTreeNode* newNode = new BTreeNode();

		int size = node->keys.size();

		for (int i = mid; i < size; i++){

			newNode->keys.push_back(node->keys[mid]);
			newNode->keysSize++;

			node->keys.erase(node->keys.begin() + mid);
			node->keysSize--;
		}
		if (!node->isLeaf()){

			int size = node->childSize;
			for (int i = mid + 1; i < size; i++){

				newNode->child.push_back(node->child[mid + 1]);
				node->child[mid + 1]->parent = newNode;
				newNode->childSize++;

				node->child.erase(node->child.begin() + mid + 1);
				node->childSize--;
			}
		}
		parent->setChild(pos + 1, newNode);
		parent->childSize++;
		newNode->parent = parent;
		node = parent;

		if (node->keysSize > 5) {

			if (node->parent == NULL)
				node = split(node);
			else
				node = split(node);
		}
	}
	return node;
}

void BTree::insert(int key, int num_keys) {
	
	if (root == NULL) {

		BTreeNode* node = new BTreeNode();
		root = node;
		node->keys.push_back(key);
		node->keysSize++;
	}
	else if (root->childSize == 0 && root->keysSize < num_keys){

		root->keys.push_back(key);
		root->keysSize++;
		//sort
		sort(root, key);
	}
	
	else if (root->childSize == 0 && root->keysSize == num_keys){
			
				root->keys.push_back(key);
				root->keysSize++;
				//sort
				sort(root, key);
				//split the root
				root=split(root);
			}
		
     else {

			BTreeNode* node = nodeForInsertion(root, key);
			//insert in the node
			node->keys.push_back(key);
			node->keysSize++;
			//sort the keys
			sort(node, key);
			//split the node if size greater than 5
			if (node->keysSize > num_keys){
				node->parent = split(node);
			}
		}
	
}

BTreeNode * BTree::nodeForInsertion(BTreeNode * node, int key) {

	int i = 0;

	if (!node->isLeaf()) {
		while (i<node->keys.size() && node->keys[i] < key) {
            i++;
		}
		BTreeNode * tempNode = (BTreeNode *)node->getChild(i);
		tempNode->parent = node;
		tempNode = nodeForInsertion(tempNode, key);
		node = tempNode;
	}
	return node;
}

void BTree::remove(int key, int num_keys){

	root;
	num_keys = 0;
	key = 0;
}

void BTree::inorder(BTreeNode * node, int key){

	int i;

	for (i = 0; i<node->keysSize; i++){

		if (node->isLeaf()==false){

			inorder((BTreeNode*)node->getChild(i), key);
		}
		vec.push_back(node->getKey(i));

		if (vec.size()>key){
			return;
		}
	}
	if (node->isLeaf()==false){

		inorder((BTreeNode*)node->getChild(i), key);
	}
}


int BTree::kthMin(int k){

	vec.clear();
	inorder(root,k);
	return vec.at(k);
}

IBTreeNode * BTree::getRoot(){

	return root;
}