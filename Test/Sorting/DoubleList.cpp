#include "DoubleList.h"
#include "DoubleNode.h"

DoubleList::DoubleList(void)
{
	head = NULL;
	tail = NULL;
}

DoubleList::~DoubleList(void)
{
}

IDoubleNode03 * DoubleList::getHead()
{
	return head;
}

IDoubleNode03 * DoubleList::getTail()
{
	return tail;
}

void DoubleList::setHead(IDoubleNode03 * head_ptr)
{
	head = head_ptr;
}

void DoubleList::setTail(IDoubleNode03 * tail_ptr)
{
	tail = tail_ptr;
}

void DoubleList::addBack(int value){

	IDoubleNode03 * temp = head;
	IDoubleNode03 * node = new DoubleNode();
	node->setValue(value);
	node->setNext(NULL);
	node->setPrev(NULL);

	if (head == NULL)
	{
		head = node;
		tail = node;
	}

	else
	{
		while (temp->getNext() != NULL){
			temp = temp->getNext();
		}
		node->setPrev(temp);
		temp->setNext(node);
		tail = node;
		
	}
}
int DoubleList::size(){

	IDoubleNode03* temp = head;
	int count = 0;

	while (temp != NULL){

		temp = temp->getNext();
		count++;
	}

	return count;
}