#include "Interfaces04.h"
#include "AVLTreeNode.h"

class AVLTree :public IAVLTree
{
public:
	AVLTreeNode * root;
	std::vector<int> vec;
	AVLTree();
	~AVLTree();
	void insert(int key);
	void remove(int key);
	int kthMin(int k) ;
	IAVLTreeNode * getRoot();
	void inorder(AVLTreeNode* node);
};