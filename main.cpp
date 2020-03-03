//main.cpp
/*
This program contains a class called "GHeap", which gives the programmer an object to use, also called "GHeap", which works as a regular heap should.
A Heap is a kind of binary tree, made up of nodes. Each node points to two (2) other nodes, and each of those point to two (2) other nodes, etc.
The program first allows the user to enter up to 100 different number inputs, then it will create a GHeap (like a heap, except I made it) and sort the numbers such that each parent is bigger than their two children. The program can handle numbers from one (1) to one-thousand (1000).
@author Greggory Hickman, March 2020
@version dev
 */

#include <iostream>
#include <cstring>
#include <stdio.h>

#include "GHeap.h"

#define LEN 100
#define BIGLEN 10000

using namespace std;

void clearCString(char*& cmdin);

int main() {
	
	bool haveInput = false;
	char* cmdin = new char[LEN];
	char* numList = new char[BIGLEN];
	
	cout << "Welcome to Gregg\'s fabulous heap program" << endl;
	
	while (true) {
		//Stay in this section until we have the input
		while (!haveInput) {
			//Clear both of our big boy cstrings
			clearCString(cmdin);
			clearCString(numList);
		
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
				char confirm;
				cin >> confirm; cin.clear(); cin.ignore(LEN, '\n');
				
				if (confirm == 'y') {
					haveInput = true;
				}
			}
			//Read from file
			else if (strcmp(cmdin, "file") == 0 || strcmp(cmdin, "f") == 0 || strcmp(cmdin, "F") == 0) {
				char* add = new char[LEN];
				FILE* fin = NULL; //Credit to my dad from showing me the FILE libraries from ye olde C
				
				clearCString(add);
				
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
				
				delete(add);
				delete(fin);
			}
			//Exit
			else if (strcmp(cmdin, "exit") == 0 || strcmp(cmdin, "e") == 0 || strcmp(cmdin, "E") == 0) {
				cout << "Closing program..." << endl;
				return 0;
			}
			//Invalid command
			else {
				cout << "Command \"" << cmdin << "\" not recognized" << endl;
			}
			cout << endl;
		}
		cout << "Input confirmed: " << numList << endl;
		haveInput = false;
		
		//Parse the input
		int input[BIGLEN];
		GHeap heap(LEN);
		
		//Print current heap
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
	delete(cmdin);
	delete(numList);
	
	return 0;
}

void clearCString(char*& cmdin) {
	for (int i = 0; i < strlen(cmdin); i++) {
		cmdin[i] = (char)0;
	}
}