#include "HeapSort.h"

HeapSort::HeapSort(){

}

HeapSort::~HeapSort(){

}

void HeapSort::sort(std::vector<int>& vector){

	int size = vector.size();

	//build heap
	for (int i = size-1; i >= 0; i--){
		fixDown(vector, i, size);
	}

	for (int j = size - 1, i = 1; j > 0; j--,i++){
		int k = vector[0];
		vector[0] = vector[j];
		vector[j] = k;
		fixDown(vector, 0, size-i);
		
	}

}

int HeapSort::leftChild(int parentIndex){

	return 2 * parentIndex + 1;
}

int HeapSort::rightChild(int parentIndex){

	return 2 * parentIndex + 2;
}


void HeapSort::fixDown(std::vector<int> & vector,int k,int size){

	
	while (leftChild(k) < size){

		int exchgIndex = leftChild(k);

		if (rightChild(k) < size){

			if (vector[exchgIndex] < vector[rightChild(k)])
				exchgIndex = rightChild(k);

		}

		if (vector[exchgIndex] > vector[k]){

			int i = vector[exchgIndex];
			vector[exchgIndex] = vector[k];
			vector[k] = i;
		}
		else
			break;

		k = exchgIndex;
	}

}
