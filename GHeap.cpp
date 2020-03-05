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
	
	highest = 0;
}

GHeap::~GHeap() {
	delete(heap);
}

int GHeap::getHighest() {
	return highest;
}

int GHeap::getParent(int address) {
	if (address < LENGTH) {
		return heap[address];
	}
	return -1; //Return -1 if the program tries to access an address which isn't allocated in memory
}

int GHeap::getChild1(int address) {
	if ((address + 1) * 2 - 1 < LENGTH) {
		return heap[(address + 1) * 2 - 1];
	}
	return -1; //Return -1 if the program tries to access an address which isn't allocated in memory
}
		
int GHeap::getChild2(int address) {
	if ((address + 1) * 2 < LENGTH) {
		return heap[(address + 1) * 2];
	}
	return -1; //Return -1 if the program tries to access an address which isn't allocated in memory
}

bool GHeap::isEmpty(int address) {
	if (heap[address] == 0) {
		return true;
	}
	else {
		return false;
	}
}

void GHeap::setParent(int address, int value) {
	if (address < LENGTH) {
		//Set that value
		heap[address] = value;
		
		//Update highest if necesary
		if (address > highest) {
			highest = address;
		}
	}
}

void GHeap::setChild1(int address, int value) {
	if ((address + 1) * 2 - 1 < LENGTH) {
		heap[(address + 1) * 2 - 1] = value;
		
		if ((address + 1) * 2 - 1 > highest) {
			highest = (address + 1) * 2 - 1;
		}
	}
}

void GHeap::setChild2(int address, int value) {
	if ((address + 1) * 2 < LENGTH) {
		heap[(address + 1) * 2] = value;
		
		if ((address + 1) * 2 > highest) {
			highest = (address + 1) * 2;
		}
	}
}
