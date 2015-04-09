#include "BTreeNode.h"


BTreeNode::BTreeNode(){

	parent = NULL;
	keysSize = 0;
	childSize = 0;
}
int BTreeNode::getKey(int index){

	return keys.at(index);
}
void BTreeNode::setKey(int index, int key){

	for (int i = index; i < keys.size(); i++){

		int temp = keys.at(i);
		keys.at(i) = key;
		key = temp;
	}

	if (key!=0)
	keys.push_back(key);

}

int BTreeNode::getKeySize()
{
	return keys.size();
}
void BTreeNode::setKeySize(int size){

	//keysSize = size;
	keys.resize(size);
}
int BTreeNode::getChildSize(){

	return child.size();
}
void BTreeNode::setChildSize(int size){
	
	//childSize = size;
	child.resize(size);
}

IBTreeNode * BTreeNode::getChild(int index)
{
	return child[index];
}

void BTreeNode::setChild(int index, IBTreeNode * c){
	
	bool flag = false;

	for (int i = index; i < child.size(); i++){

		if (child.size() == 0){

			flag = true;
			child.push_back((BTreeNode*)c);
			break;
		}
		BTreeNode* temp = child.at(i);
		child.at(i)=(BTreeNode*)c;
		c = temp;
	}

	if (c!=NULL && !flag)
	child.push_back((BTreeNode*)c);
}
bool BTreeNode::isLeaf(){

	if (childSize == 0){
		return true;
	}
	else
		return false;
}
