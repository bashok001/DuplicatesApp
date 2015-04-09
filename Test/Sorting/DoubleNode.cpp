#include "DoubleNode.h"

void DoubleNode::setValue(int value)
{
	data = value;
}

int DoubleNode::getValue()
{
	return data;
}

IDoubleNode03 * DoubleNode::getPrev()
{
	return prev_ptr;
}

IDoubleNode03 * DoubleNode::getNext()
{
	return next_ptr;
}

void DoubleNode::setPrev(IDoubleNode03 * prev)
{
	prev_ptr = prev;
}

void DoubleNode::setNext(IDoubleNode03 * next)
{
	next_ptr = next;
}

