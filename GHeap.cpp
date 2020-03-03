//GHeap.cpp

#include "GHeap.h"

//Constructor
GHeap::GHeap(int LENGTH) {
	this->LENGTH = LENGTH;
	heap = new int[LENGTH];
	
	//Set all initial values to be 0, which is my version of null from this project, because real numbers can only be from 1 to 1000
	for (int i = 0; i < LENGTH; i++) {
		heap[i] = i;
	}
}

GHeap::~GHeap() {
	delete(heap);
}

int* GHeap::getRaw() {
	return heap;
}

int GHeap::getParent(int address) {
	return heap[address];
}

void GHeap::setParent(int address, int value) {
	heap[address] = value;
}

void GHeap::setChildren(int parentAddress, int child1, int child2) {
	heap[parentAddress * 2] = child1;
	heap[parentAddress * 2 + 1] = child1;
}
