#pragma once
#include "Interfaces01.h"
#include <string>

class DoubleNode : public IDoubleNode
{
	int data;
	IDoubleNode * next_ptr, *prev_ptr;
public:
	DoubleNode() {};
	~DoubleNode() {};
	void setValue(int value);
	int getValue();
	IDoubleNode * getPrev();
	IDoubleNode * getNext();
	void setPrev(IDoubleNode * prev);
	void setNext(IDoubleNode * next);
};

