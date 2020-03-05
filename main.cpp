//main.cpp
/*
This program contains a class called "GHeap", which gives the programmer an object to use, also called "GHeap", which works as a regular heap should.
A Heap is a kind of binary tree, made up of nodes. Each node points to two (2) other nodes, and each of those point to two (2) other nodes, etc.
The program first allows the user to enter up to 100 different number inputs, then it will create a GHeap (like a heap, except I made it) and sort the numbers such that each parent is bigger than their two children. The program can handle numbers from one (1) to one-thousand (1000).

void insertToken(GHeap& heap, int address, int newToken) - A recursive method which takes an address of a GHeap and a new token which must be sorted into it correctly to create a correct max heap. It also calls in the pointer to the GHeap in question
GHeap maxHeapSort(int*) - Input an array on ints and put them into a heap, sorted such that the heap is a max heap.
void printHeap(GHeap) - Print out the passed in heap in a visual manner
int* parseInput(char*) - Takes in a cstring of numbers separated by spaces, and outputs those same numbers put into an int array. All non-numbers will be ignored.
char* getInput(bool&) - Asks for and returns the user's input either through the console, or by reading from a file. If the exit command is triggered, then it will change Am I modular yet????????
void clearCString(char*&, int) - Clears a cstring of preallocated ram from random other things of length "len". There's probably already something else out there that does this exact thing, but this was really easy to make so I don't care.

@author Greggory Hickman, March 2020
@version 1.0
 */

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "GHeap.h"

#define LEN 101 //If it's at exactly 100, sometimes seg faults happen
#define BIGLEN 30000

using namespace std;

void insertToken(GHeap& heap, int address, int newToken);
GHeap maxHeapSort(int*);
void printHeap(GHeap*);
int* parseInput(char*);
char* getInput(bool&);
void clearCString(char*&, int);

int main() {
	
	//Define some variables and objects that we will need throughout the program
	bool quit = false;
	
	char* numList;
	
	cout << "Welcome to Gregg\'s fabulous heap program" << endl;
	
	//The loop that the majority of the program takes place in
	while (!quit) {
		numList = getInput(quit); //Get the input from the user using a series of prompts
		//Quit if the quit command was run inside of getInput()
		if (quit) {
			return 0;
		}
		
		//Parse the char* input into an int* with each number separated
		int* numStream = parseInput(numList);
		
		//Print out the parsed input to show the user exactly what will be used in the heap
		cout << "Input confirmed: ";
		for (int i = 0; numStream[i] != 0; i++) cout << numStream[i] << " "; //Print all int-ified inputs
		cout << endl << endl;
		
		//Ask to sort into a max heap (in case somebody wants to expand this code in the future to do things other than just max heap)
		cout << "Sorting into max heap..." << endl;
		GHeap heap = maxHeapSort(numStream); //Sort numStream into max heap
		cout << endl;
		
		//Print current heap
		printHeap(&heap);
	}
	
	return 0;
}

void insertToken(GHeap* heap, int address, int newToken) {
	//cout << "New Token: " << newToken << ", ";
	//printHeap(heap);
	
	//Replace the current token at address with input[i]
	int oldToken = heap->getParent(address);
	heap->setParent(address, newToken);
	
	//Start the cycle again if necesary
	//If the old token wasn't 0 (this is here because without it, the zeroes all the way down the chain would compare themselves to each other needlessly, which would be super-mega inefficient)
	if (oldToken != 0) {
		//If either child doesn't exist yet, set the oldToken as the new child
		if (heap->getChild1(address) == 0) {
			heap->setChild1(address, oldToken);
			return;
		}
		if (heap->getChild2(address) == 0) {
			heap->setChild2(address, oldToken);
			return;
		}
		
		//Otherwise, start the cycle again
		insertToken(heap, (address + 1) * 2 - 1, oldToken);
	}
}

GHeap maxHeapSort(int* input) {
	
	GHeap heap(BIGLEN);
	//For future reference, the "boss parent" is the very first node; the one which all others lead back to
	//
	//For every token in input...
	for (int i = 0; input[i] != 0; i++) { //i is iterator for input
		for (int j = 0; j < LEN; j++) { //j is iterator for heap
			//... and go through the heap from left to right until a token of lower magnitude than the current number from input is found.
			//At which point replace the new token with the old, then recursively sort down the tree from that point.
			if (input[i] >= heap.getParent(j)) {
				//Sort the new token and all of its children
				insertToken(&heap, j, input[i]);
				break;
			}
		}
	}
	
	return heap;
}

void printHeap(GHeap* heap) {
	//A semi-okay method for displaying the heap
	/*
	cout << "&heap in printHeap" << heap.heap << endl;
	bool odd = false;
	for (int i = 0; i < LEN; i++) {
		char child;
		if (odd == true)
			child = 'a';
		else
			child = 'b';
		
		cout << "After New C1: " << heap.heap[i] << endl << endl;
		if (i == 0) {
			cout << "Master parent: " << heap.getParent(i) << endl;
		}
		else {
			cout << "Pair " << (i + 3) / 2 << child << ": " << heap.getParent(i) << endl;
		}
		odd = !odd;
		
		cout << "After New C2: " << heap.heap[i] << endl << endl;
	}
	*/
	
	//A much better method for displaying the heap
	int limit = -1;
	int generation = 0;
	bool even = true;
	cout << "Note: Numbers that come from the same parent are held together by parentheses, e.g. (4 2)." << endl;
	
	cout << "Heap Tree: ";
	//An algorithm for separating the generations properly
	for (int i = 0; i < BIGLEN; i++) {
		//If there are no more tokens, then just stop printing empty slots
		if (i > heap->getHighest()) {
			break;
		}
		//If generation is over, start a new line
		if (i + 2 >= limit * 2 + 1) {
			cout << endl;
			cout << "Generation " << ++generation << ": "; //Announce the new generation
			limit = i + 1;
		}
		//If the token is not empty, print it to console.
		if (!heap->isEmpty(i)) {
			//If the token address is odd or if it is the master parent, put an open parenthesis before it
			if (!even || generation == 1) {
				cout << "(";
			}
			
			cout << heap->getParent(i);
			
			//If the token address is even, put a close parenthesis after it, and indent the next set
			//Or if the token address is odd but the token has no sibbling, put a close parenthesis after it as well
			if (even || heap->isEmpty(i + 1)) { 
				cout << ")";
			}
		}
		//If the token is empty, but the generation is not over (so that any gaps in between child groups don't cause parent-child mix up visually)
		else {
			cout << "()";
		}
		
		cout << " ";
		even = !even; //Reverse polarity of even
	}
	cout << endl << endl;
	
}

int* parseInput(char* numList) {
	char* current = new char[LEN];
	int* numStream = new int[LEN];
	
	//Clear pesky leftover ram from pointer arrays
	
	clearCString(current, LEN);
	for (int i = 0; i < LEN; i++) {
		numStream[i] = 0;
	}
	
	//cout << "Starting numList: " << numList << endl;
	//cout << "Starting current: " << current << endl;
	
	//Parse the input
	int j = 0; //Iterator for current
	int k = 0; //Iterator for numStream
	for (int i = 0; i < BIGLEN + 1; i++) {
		//If we have hit the 100 number max limit
		if (k >= LEN - 1) {
			break;
		}
		//If is number
		if (numList[i] >= 48 && numList[i] <= 57) {
			//Add the digit to the end of the current multi-digit number
			current[j] = numList[i];
			j++;
		}
		//If is space
		else if (numList[i] == 32) {
			if (j != 0) {
				//cout << "Space: " << current << endl;
				//current contains the number that we want to convert to an integer
				int next = 0;
				
				//Iterate backwards through current
				for (int l = j - 1; l >= 0; l--) {
					//Convert the char* to int one unit place at a time by adding each value * 10^place. For example, when in the hundred's place, place = 2.
					next += (current[l] - 48) * round(pow(10, j - l - 1));
				}
				//cout << "Next: " << next << endl;
				numStream[k] = next;
				j = 0;
				k++;
				
				clearCString(current, LEN);
			}
		}
		//If is null
		else if (numList[i] == 0) {
			if (j != 0) {
				//cout << "Null: " << current << endl;
				//current contains the number that we want to convert to an integer
				int next = 0;
				
				//Iterate backwards through current
				for (int l = j - 1; l >= 0; l--) {
					//Convert the char* to int one unit place at a time by adding each value * 10^place. For example, when in the hundred's place, place = 2.
					next += (current[l] - 48) * round(pow(10, j - l - 1));
				}
				numStream[k] = next;
				break;
			}
		}
	}
	delete(current);
	
	return numStream;
}

char* getInput(bool& quit) {
	
	bool haveInput = false;
	char cmdin[LEN];
	char* numList = new char[BIGLEN];
	
	//Stay in this section until we have the input
	while (!haveInput) {
		//Clear both of our big boy cstrings
		clearCString(numList, BIGLEN);
	
		//Ask how the user wants to input the numbers
		cout << "Type \"console\" to type your numbers straight into the console " << endl << 
		"Type \"file\" to read from file " << endl << 
		"Type \"exit\" to kill the program" << endl;
	
		cout << "> ";
		cin >> cmdin; cin.clear(); cin.ignore(LEN, '\n');
		
		cout << endl;
		//Read from console
		if (strcmp(cmdin, "console") == 0 || strcmp(cmdin, "c") == 0 || strcmp(cmdin, "C") == 0) {
			cout << "Reading from console..." << endl <<
			"Input your number inputs, each separated by a space" << endl;
			
			//Read in the input from console and put it into numList
			cout << "Console> ";
			cin.getline(numList, BIGLEN);
	
			//At this point, we have our input (numList). Now, let's confirm that it's what the user wants.
			cout << "Input: " << numList << endl;
			cout << "Confirm Input? (y/n)" << endl;
			cout << "> ";
			char confirm;
			cin >> confirm; cin.clear(); cin.ignore(LEN, '\n');
			
			if (confirm == 'y') {
				haveInput = true;
			}
		}
		//Read from file
		else if (strcmp(cmdin, "file") == 0 || strcmp(cmdin, "f") == 0 || strcmp(cmdin, "F") == 0) {
			char add[LEN];
			FILE* fin = NULL; //Credit to my dad from showing me the FILE libraries from ye olde C
			
			cout << "Reading from file..." << endl <<
			"Input the path to your file. It must be a text file:" << endl;
			
			//Get address
			cout << "File> ";
			cin.getline(add, LEN);
			
			//Get file from address
			fin = fopen(add, "r"); //"r" for read
			
			if (fin != NULL) {
				//Put the contents of the file into numList
				fgets(numList, BIGLEN, fin);
				
				//At this point, we have our input (numList). Now, let's confirm that it's what the user wants before we ship it back out to the main method
				cout << "Input: " << numList << endl;
				cout << "Confirm Input? (y/n)" << endl;
				cout << "> ";
				char confirm;
				cin >> confirm; cin.clear(); cin.ignore(LEN, '\n');
				
				if (confirm == 'y') {
					haveInput = true;
				}
			}
			else {
				cout << "There was an issue opening the file at \"" << add << "\". Please try again" << endl;
			}
			fclose(fin);
			
			delete(fin);
		}
		//Exit
		else if (strcmp(cmdin, "exit") == 0 || strcmp(cmdin, "e") == 0 || strcmp(cmdin, "E") == 0) {
			cout << "Closing program..." << endl;
			quit = true; //Set the bool pointer to true, which will trigger the program to end back in the main method
			return NULL;
		}
		//Invalid command
		else {
			cout << "Command \"" << cmdin << "\" not recognized" << endl;
		}
		cout << endl;
	}
	
	//Return the complete input
	return numList;
}

void clearCString(char*& in, int len) {
	for (int i = 0; i < len; i++) {
		in[i] = (char)0;
	}
}

//Ignore all of this. This used to be in the maxHeapSort method.
/*
cout << "Position: " << j << endl;
cout << "Old: " << heap.getParent(j) << endl;
cout << "New: " << input[i] << endl;
cout << "Child 1: " << heap.getChild1(j) << ", Child 2: " << heap.getChild2(j) << endl << endl;

int temp = heap.getParent(j);
heap.setParent(j, input[i]);

if (temp >= heap.getChild1(j)) {
	int temp = heap.getParent(j);
	heap.setParent(j, input[i]);
}
if (temp >= heap.getChild2(j)) {
	int temp = heap.getParent(j);
	heap.setParent(j, input[i]);
}

//If either child doesn't exist yet, make the old token one of the new token's children

if (heap.getChild1(j) == 0) {
	heap.setChild1(j, temp);
	
	cout << "After New B1: " << heap.getParent(j) << endl << endl;
	cout << "&heap" << heap.heap << endl;
	//printHeap(heap); //Uncommenting these causes a very strange glitch
	cout << "After New B2: " << heap.getParent(j) << endl << endl;
	break;
}
else if (heap.getChild2(j) == 0) {
	heap.setChild2(j, temp);
	
	cout << "After New B1: " << heap.getParent(j) << endl << endl;
	//printHeap(heap);
	cout << "After New B2: " << heap.getParent(j) << endl << endl;
	break;
}

cout << "After New B: " << heap.getParent(j) << endl << endl;



//Otherwise if both children already exist, then do the above test on them
for (int k = 0; k < 10; k++) {
	
}


break;
*/