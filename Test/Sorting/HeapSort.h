#include "Interfaces03.h"

class HeapSort : public IHeapSort{
public:
	HeapSort();
	~HeapSort();
	void sort(std::vector<int>& vector);
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	void fixDown(std::vector<int>& vector,int k,int size);
};