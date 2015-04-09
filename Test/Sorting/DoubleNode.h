#pragma once
#include "Interfaces03.h"

class DoubleNode : public IDoubleNode03
{
	int data;
	IDoubleNode03 * next_ptr, *prev_ptr;
public:
	DoubleNode() {};
	~DoubleNode() {};
	void setValue(int value);
	int getValue();
	IDoubleNode03 * getPrev();
	IDoubleNode03 * getNext();
	void setPrev(IDoubleNode03 * prev);
	void setNext(IDoubleNode03 * next);
};

