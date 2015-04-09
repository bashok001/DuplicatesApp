#include "Interfaces04.h"

class AVLTreeNode : public IAVLTreeNode
{
public:

	IAVLTreeNode* leftNode;
	IAVLTreeNode* rightNode;
	IAVLTreeNode* parentNode;
	int height;
	int value;

	AVLTreeNode();
	~AVLTreeNode();
	void setLeft(IAVLTreeNode * left);
	void setRight(IAVLTreeNode * right);
	void setParent(IAVLTreeNode * parent);
	void setKey(int key);
	void setHeight(int ht);
	IAVLTreeNode * getLeft();
	IAVLTreeNode * getRight();
	IAVLTreeNode * getParent();
	int getKey();
	int getHeight();
};