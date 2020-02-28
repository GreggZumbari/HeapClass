//main.cpp

#include <iostream>
#include <cstring>

#include "GHeap.h"

#define LEN 10000

using namepsace std;

int main() {
	
	char* in = new int[LEN];
	
	cout << "Welcome to The Heap Shack! How may I take your order?" << endl
	<< "(Type \"console\" to type from console, Type \"file\" to read from file)" << endl;

	cin.getline(in, LEN);

	//Read from console
	if (strcmp(in, "console") == 0 || strcmp(in, "c") == 0 || strcmp(in, "C") == 0) {
		
	}
}

void clearCString(char*& in) {
	for (int i = 0; i < strlen(in); i++) {
		in[i] = '\0';
	}
	return in;
}