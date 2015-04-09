#include "AVLTreeNode.h"

AVLTreeNode::AVLTreeNode(){
	leftNode = NULL;
	rightNode = NULL;
	parentNode = NULL;
	height = 1;
	value = 0;
}

AVLTreeNode::~AVLTreeNode(){

}

void AVLTreeNode::setLeft(IAVLTreeNode * left){

	leftNode = left;
}

void AVLTreeNode::setRight(IAVLTreeNode * right){

	rightNode = right;
}

void AVLTreeNode::setParent(IAVLTreeNode * parent){
	parentNode = parent;
}

void AVLTreeNode::setKey(int key){

	value = key;

}

void AVLTreeNode::setHeight(int ht){

	height = ht;

}

IAVLTreeNode * AVLTreeNode::getLeft(){

	return leftNode;
}

IAVLTreeNode * AVLTreeNode::getRight(){

	return rightNode;
}

IAVLTreeNode * AVLTreeNode::getParent(){

	return parentNode;
}

int AVLTreeNode::getKey(){

	return value;
}

int AVLTreeNode::getHeight(){

	return height;
}