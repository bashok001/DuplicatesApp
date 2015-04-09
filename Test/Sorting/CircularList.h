#pragma once
#include "Interfaces03.h"

class CircularList :ICircularList {
public:
	ISingleNode03* tail_ptr;
	CircularList();
	~CircularList();
	void addHead(int number);
	ISingleNode03 * getTail();
	void setTail(ISingleNode03 * tail);
	int size();
};