#pragma once
#include "Interfaces01.h"
#include <string>

class DoubleList : public IDoubleList
{
	IDoubleNode * head, *tail;
public:
	DoubleList(void);
	~DoubleList(void);
	IDoubleNode * getHead();
	IDoubleNode * getTail();
	void setHead(IDoubleNode * head_ptr);
	void setTail(IDoubleNode * tail_ptr);
	void addSorted(int value);
	void orderSort2();
	void orderSort3();
	void sequenceOrderSort();
	void reverse();
};

