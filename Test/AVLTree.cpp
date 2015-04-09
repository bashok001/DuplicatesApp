#include "AVLTree.h"


AVLTree::AVLTree(){
	root = NULL;
}

AVLTree::~AVLTree(){

}

AVLTreeNode* rightRotation(AVLTreeNode* node){

	if (node->getLeft() == NULL)
		return node;

	AVLTreeNode* parent = (AVLTreeNode*)node->getLeft();
	AVLTreeNode* grandParent = (AVLTreeNode*)node->getParent();

	//right node to left of current node
	AVLTreeNode* newLeftNode = NULL;

	if (parent->getRight() != NULL){
		newLeftNode = (AVLTreeNode*)parent->getRight();
	}

	node->setLeft(newLeftNode);

	if (newLeftNode != NULL)
		((AVLTreeNode*)newLeftNode)->setParent(node);

	//set new parent
	parent->setRight(node);
	node->setParent(parent);
	parent->setParent(grandParent);

	//set the grandparent
	if (grandParent != NULL && grandParent->getLeft() == node){

		grandParent->setLeft(parent);
	}

	if (grandParent != NULL && grandParent->getRight() == node){

		grandParent->setRight(parent);
	}

	//adjust height of node
	int rht = 0;
	int lht = 0;

	if (node->getRight() != NULL){
		rht = ((AVLTreeNode*)node->getRight())->getHeight();
	}

	if (node->getLeft() != NULL){

		lht = ((AVLTreeNode*)node->getLeft())->getHeight();
	}
	if (lht > rht){
		node->setHeight(lht + 1);
	}
	else
	{
		node->setHeight(rht + 1);
	}

	//adjust height of parent
	rht = 0;
	lht = 0;
	if (parent->getRight() != NULL){
		rht = ((AVLTreeNode*)parent->getRight())->getHeight();
	}

	if (parent->getLeft() != NULL){

		lht = ((AVLTreeNode*)parent->getLeft())->getHeight();
	}
	if (lht > rht){
		parent->setHeight(lht + 1);
	}
	else
	{
		parent->setHeight(rht + 1);
	}


	////adjust height of node
	//rht = 0;
	//lht = 0;

	//if (node->getRight() != NULL){
	//	rht = ((AVLTreeNode*)node->getRight())->getHeight();
	//}

	//if (node->getLeft() != NULL){

	//	lht = ((AVLTreeNode*)node->getLeft())->getHeight();
	//}
	

	return parent;
}

AVLTreeNode * leftRotation(AVLTreeNode * node) {


	if (node->getRight() == NULL)
		return node;

	AVLTreeNode* parent = (AVLTreeNode*)node->getRight();
	AVLTreeNode* grandParent = (AVLTreeNode*)node->getParent();

	//left node to right of current node
	AVLTreeNode* newRightNode = NULL;

	if (parent->getLeft() != NULL){
		newRightNode = (AVLTreeNode*)parent->getLeft();
	}

	node->setRight(newRightNode);

	if (newRightNode != NULL)
		((AVLTreeNode*)newRightNode)->setParent(node);

	//set new parent
	parent->setLeft(node);
	node->setParent(parent);
	parent->setParent(grandParent);

	//set the grandparent
	if (grandParent != NULL && grandParent->getLeft() == node){

		grandParent->setLeft(parent);
	}

	if (grandParent != NULL && grandParent->getRight() == node){

		grandParent->setRight(parent);
	}



	//adjust height of node
	int rht = 0;
	int lht = 0;

	if (node->getRight() != NULL){
		rht = ((AVLTreeNode*)node->getRight())->getHeight();
	}

	if (node->getLeft() != NULL){

		lht = ((AVLTreeNode*)node->getLeft())->getHeight();
	}

	if (lht > rht){
		node->setHeight(lht + 1);
	}
	else
	{
		node->setHeight(rht + 1);
	}


	//adjust height of parent
	rht = 0;
	lht = 0;
	if (parent->getRight() != NULL){
		rht = ((AVLTreeNode*)parent->getRight())->getHeight();
	}

	if (parent->getLeft() != NULL){

		lht = ((AVLTreeNode*)parent->getLeft())->getHeight();
	}
	if (lht > rht){
		parent->setHeight(lht + 1);
	}
	else
	{
		parent->setHeight(rht + 1);
	}


	return parent;
}

AVLTreeNode* rotation(IAVLTreeNode* node){

	AVLTreeNode *prev = NULL, *curr = (AVLTreeNode *)node;
	int height = 0;

	int balancingFactor = 0;

	while (curr != NULL){

		int rht = 0;
		int lht = 0;

		if (curr->getRight() != NULL){
			rht = ((AVLTreeNode*)curr->getRight())->getHeight();
		}

		if (curr->getLeft() != NULL){

			lht = ((AVLTreeNode*)curr->getLeft())->getHeight();
		}
		if (lht > rht){
			height = lht + 1;
		}
		else
		{
			height = rht + 1;
		}

		curr->setHeight(height);
		balancingFactor = rht - lht;

		if (balancingFactor < -1){

			if (node->getKey() < curr->getLeft()->getKey()){
				curr = rightRotation(curr);
			}

			else{
				curr->setLeft(leftRotation((AVLTreeNode*)curr->getLeft()));
				curr = rightRotation(curr);
			}

		}

		else if (balancingFactor > 1){

			if (node->getKey() > curr->getRight()->getKey()){
				curr = leftRotation(curr);
			}

			else{
				curr->setRight(rightRotation((AVLTreeNode*)curr->getRight()));
				curr = leftRotation(curr);
			}

		}
		prev = curr;
		curr = (AVLTreeNode*)curr->getParent();
	}


	return prev;
}

void AVLTree::insert(int key){

	IAVLTreeNode* curr = NULL, *prev = NULL;

	if (root == NULL){

		AVLTreeNode* node = new AVLTreeNode();
		node->setKey(key);
		root = node;
	}
	else{

		AVLTreeNode* node = new AVLTreeNode();
		node->setKey(key);
		curr = root;
		while (curr != NULL)
		{

			if (key < curr->getKey())
			{
				prev = curr;
				curr = curr->getLeft();
			}
			//to check
			else //if (key > curr->getKey())
			{
				prev = curr;
				curr = curr->getRight();
			}
		}

		if (key < prev->getKey()){

			node->setParent(prev);
			prev->setLeft(node);
		}
		else{
			node->setParent(prev);
			prev->setRight(node);
		}

		root = rotation(node);

	}



}

AVLTreeNode * deleteNode(AVLTreeNode * node) {

	AVLTreeNode* parent = (AVLTreeNode*)node->getParent();

	bool isRightChild = false, isLeftChild = false;
    if (parent !=NULL && parent->getLeft() == node){
	       isLeftChild = true;
		}
		else if (parent != NULL && parent->getRight() == node){
			isRightChild = true;
		}

	if (node->getLeft() == NULL && node->getRight() == NULL) {

		if (parent == NULL)
			return NULL;
		else {

			node = NULL;

			if (isLeftChild)
				parent->setLeft(NULL);
			else if (isRightChild)
				parent->setRight(NULL);

			rotation(parent);
		}
	}

	else if (node->getLeft() == NULL || node->getRight() == NULL) {
		
		        AVLTreeNode* temp = NULL;
				if (node->getLeft() != NULL){
					temp = (AVLTreeNode*)node->getLeft();
				}
				else if (node->getRight() != NULL){
					temp = (AVLTreeNode*)node->getRight();
				}
		        node = NULL;
		
				if (isLeftChild){
					parent->setLeft(temp);
					temp->setParent(parent);
				}
				else if (isRightChild){
					parent->setRight(temp);
					temp->setParent(parent);
				}
		
				rotation(temp);
				
	}
	else if (node->getLeft() != NULL && node->getRight() != NULL) {

		AVLTreeNode* temp = (AVLTreeNode*)node->getLeft();
		
				while (temp->getRight() != NULL){
					temp = (AVLTreeNode*)temp->getRight();
				}
				node->setKey(temp->getKey());
				deleteNode(temp);
				rotation(temp->getParent());
	}


}

void AVLTree::remove(int key){

	IAVLTreeNode* curr = NULL;

	if (root == NULL){
		return;
	}
	curr = root;

	while (curr != NULL){

		if (key < curr->getKey()){
			curr = (AVLTreeNode*)curr->getLeft();
		}
		else if (key > curr->getKey()){
			curr = (AVLTreeNode*)curr->getRight();
		}
		else{
			deleteNode((AVLTreeNode*)curr);
			return;
		}
	}
}

void AVLTree::inorder(AVLTreeNode* node){

	if (node == NULL)
		return ;

	inorder((AVLTreeNode*)node->getLeft());
	vec.push_back(node->getKey());
	inorder((AVLTreeNode*)node->getRight());

}

int AVLTree::kthMin(int k){

	inorder((AVLTreeNode*)root);
	int kth = vec[k];
	vec.clear();
	return kth;
}

IAVLTreeNode * AVLTree::getRoot(){

	return root;

}