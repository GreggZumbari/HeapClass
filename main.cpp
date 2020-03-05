//main.cpp
/*
This program contains a class called "GHeap", which gives the programmer an object to use, also called "GHeap", which works as a regular heap should.
A Heap is a kind of binary tree, made up of nodes. Each node points to two (2) other nodes, and each of those point to two (2) other nodes, etc.
The program first allows the user to enter up to 100 different number inputs, then it will create a GHeap (like a heap, except I made it) and sort the numbers such that each parent is bigger than their two children. The program can handle numbers from one (1) to one-thousand (1000).

GHeap maxHeapSort(int*) - Input an array on ints and put them into a heap, sorted such that the heap is a max heap.
void printHeap(GHeap) - Print out the passed in heap in a visual manner
int* parseInput(char*) - Takes in a cstring of numbers separated by spaces, and outputs those same numbers put into an int array. All non-numbers will be ignored.
char* getInput(bool&) - Asks for and returns the user's input either through the console, or by reading from a file. If the exit command is triggered, then it will change Am I modular yet????????
void clearCString(char*&, int) - Clears a cstring of preallocated ram from random other things of length "len". There's probably already something else out there that does this exact thing, but this was really easy to make so I don't care.

@author Greggory Hickman, March 2020
@version dev
 */

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <math.h>

#include "GHeap.h"

#define LEN 100
#define BIGLEN 10000

using namespace std;

GHeap maxHeapSort(int*);
void printHeap(GHeap);
int* parseInput(char*);
char* getInput(bool*&);
void clearCString(char*&, int);

int main() {
	
	//Define some variables and objects that we will need throughout the program
	bool* quit = new bool();
	*quit = false;
	
	char* numList = new char[BIGLEN];
	clearCString(numList, BIGLEN);
	
	cout << "Welcome to Gregg\'s fabulous heap program" << endl;
	
	//The loop that the majority of the program takes place in
	while (!(*quit)) {
		//Get the input from the user using a series of prompts
		numList = getInput(quit);
		//Quit if the quit command was run inside of getInput()
		if (*quit) {
			return 0;
		}
		
		//Parse the char* input into an int* with each number separated
		int* numStream = parseInput(numList);
		
		cout << "Input confirmed: ";
		for (int i = 0; numStream[i] != 0; i++) cout << numStream[i] << " "; //Print all int-ified inputs
		cout << endl << endl;
		
		//Print current heap
		//printHeap(heap);
	}
	
	return 0;
}

GHeap maxHeapSort(int* numList) {
	
}

void printHeap(GHeap heap) {
	bool odd = false;
	for (int i = 0; i < LEN; i++) {
		char child;
		if (odd == true)
			child = 'a';
		else
			child = 'b';
		
		if (i == 0) {
			cout << "Gen 1: " << heap.getParent(i) << endl;
		}
		else {
			cout << "Gen " << (i + 3) / 2 << child << ": " << heap.getParent(i) << endl;
		}
		odd = !odd;
	}
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
	for (int i = 0; i < strlen(numList) + 1; i++) {
		//If is number
		if (numList[i] >= 48 && numList[i] <= 57) {
			current[j] = numList[i];
			//cout << " Current: " << current << endl;
			//cout << " Current[" << j << "]: " << current[j];
			//cout << " numList: " << numList[i] << endl;
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
					//cout << "Current[" << l << "]: " << current[l] << endl;
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
					next += (current[l] - 48) * pow(10, j - l - 1);
					//cout << "Pow: " << j - l << endl;
					//cout << "Current: " << next << ", " << current[l] * pow(10, j - l) << endl;
				}
				numStream[k] = next;
				break;
			}
		}
	}
	delete(current);
	
	return numStream;
}

char* getInput(bool*& quit) {
	
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
			cin.getline(numList, LEN);
	
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
				fgets(numList, LEN, fin);
				
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
			else {
				cout << "There was an issue opening the file at \"" << add << "\". Please try again" << endl;
			}
			fclose(fin);
			
			delete(fin);
		}
		//Exit
		else if (strcmp(cmdin, "exit") == 0 || strcmp(cmdin, "e") == 0 || strcmp(cmdin, "E") == 0) {
			cout << "Closing program..." << endl;
			*quit = true; //Set the bool pointer to true, which will trigger the program to end back in the main method
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