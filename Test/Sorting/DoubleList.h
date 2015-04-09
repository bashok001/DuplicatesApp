#pragma once
#include "Interfaces03.h"


class DoubleList : public IDoubleList03
{
	IDoubleNode03 * head, *tail;
public:
	DoubleList(void);
	~DoubleList(void);
	IDoubleNode03 * getHead();
	IDoubleNode03 * getTail();
	void setHead(IDoubleNode03 * head_ptr);
	void setTail(IDoubleNode03 * tail_ptr);
	void addBack(int value);
	int size();
	
};

