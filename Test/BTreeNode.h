#include "Interfaces04.h"

class BTreeNode :public IBTreeNode
{
public:
	std::vector<int> keys;
	std::vector<BTreeNode*> child;
	BTreeNode * parent;
	int childSize;
	int keysSize;
    std::vector<int> vec;
	BTreeNode();
	~BTreeNode() {}
	int getKey(int index);
	void setKey(int index, int key) ;
	int getKeySize() ;
	void setKeySize(int size) ;
	int getChildSize() ;
	void setChildSize(int size);
	IBTreeNode * getChild(int index) ;
	void setChild(int index, IBTreeNode * child);
	bool isLeaf();
};