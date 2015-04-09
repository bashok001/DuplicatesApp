#include "CircularList.h"
#include "SingleNode.h"

CircularList::CircularList(){
	tail_ptr = NULL;
}
CircularList::~CircularList(){

}
void CircularList::addHead(int number){

	ISingleNode03* newNode = new SingleNode();
	newNode->setValue(number);

	if (tail_ptr == NULL){

		tail_ptr = newNode;
		tail_ptr->setNext(tail_ptr);
	}
	else{
		newNode->setNext(tail_ptr->getNext());
		tail_ptr->setNext(newNode);
	}

}


ISingleNode03* CircularList::  getTail(){

	return tail_ptr;
}

void CircularList::setTail(ISingleNode03 * tail){

	tail_ptr = tail;
}


int CircularList::size(){

	if (tail_ptr != NULL){

		int size = 1;
		ISingleNode03 * curr = tail_ptr->getNext();
		while (curr != tail_ptr){
			size++;
			curr = curr->getNext();
		}
		return size;
	}
	else return 0;
}