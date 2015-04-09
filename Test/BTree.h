#include "Interfaces04.h"
#include "BTreeNode.h"

class BTree : public IBTree{

public:
	BTreeNode* root;
	std::vector<int> vec;

	BTree();
    ~BTree() { }
	void insert(int key, int num_keys);
	void remove(int key, int num_keys) ;
	int kthMin(int k) ;
	IBTreeNode * getRoot() ;
	BTreeNode* split(BTreeNode* node);
	BTreeNode * nodeForInsertion(BTreeNode * node, int key);
	void inorder(BTreeNode* node,int key);
};