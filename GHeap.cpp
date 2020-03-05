//GHeap.cpp

#include "GHeap.h"

//Constructor
GHeap::GHeap(int LENGTH) {
	this->LENGTH = LENGTH;
	heap = new int[LENGTH];
	
	//Set all initial values to be 0, which is my version of null for this project because real numbers can only be from 1 to 1000
	for (int i = 0; i < LENGTH; i++) {
		heap[i] = 0;
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

int GHeap::getChild1(int address) {
	return heap[(address + 1) * 2 - 1];
}
		
int GHeap::getChild2(int address) {
	return heap[(address + 1) * 2];
}

void GHeap::setParent(int address, int value) {
	heap[address] = value;
}

void GHeap::setChildren(int parentAddress, int child1, int child2) {
	heap[(parentAddress + 1) * 2 - 1] = child1;
	heap[(parentAddress + 1) * 2] = child2;
}
