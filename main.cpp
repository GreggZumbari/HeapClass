//main.cpp

#include <iostream>
#include <cstring>

#include "GHeap.h"

#define LEN 100
#define BIGLEN 10000

using namespace std;

void clearCString(char*& cmdin);

int main() {
	
	char* cmdin = new char[LEN];
	char* numin = new char[BIGLEN];
	
	cout << "Welcome to Gregg\'s fabulous heap program" << endl;
	
	while (true) {
		clearCString(cmdin);
	
		cout << "Type \"console\" to type from console " << endl << 
		"Type \"file\" to read from file " << endl << 
		"Type \"exit\" to kill the program" << endl;
	
		cout << "Horp> ";
		cin >> cmdin; cin.clear(); cin.ignore(LEN, '\n');
		
		cout << endl;
		//Read from console
		if (strcmp(cmdin, "console") == 0 || strcmp(cmdin, "c") == 0 || strcmp(cmdin, "C") == 0) {
			cout << "Reading from console..." << endl <<
			"Input your number inputs, each separated by a space" << endl;
			
			cout << "Horp> ";
			cin.getline(numin, LEN);
	
			//At this point, we have our input
			cout << numin << endl;
		}
		//Read from file
		else if (strcmp(cmdin, "file") == 0 || strcmp(cmdin, "f") == 0 || strcmp(cmdin, "F") == 0) {
			char* add = new char[LEN];
			FILE* fin; //Credit to my dad from showing me the FILE libraries from ye olde C
			
			clearCString(fileCont);
			clearCString(add);
			
			cout << "Reading from file..." << endl <<
			"Input the path to your file. It must be a text file:" << endl;
			
			//Get address
			cout << "File> ";
			cin.getline(add, LEN);
			
			//Get file from address
			fin = fopen(add, "r"); //"r" for read
			fgets(fileCont, LEN, fin);
			fclose(fin);
			
			cout << "File contents: " << fileCont << endl;
			
			delete(add);
			delete(fileCont);
		}
		//Exit
		else if (strcmp(cmdin, "exit") == 0 || strcmp(cmdin, "e") == 0 || strcmp(cmdin, "E") == 0) {
			cout << "Closing program..." << endl;
			break;
		}
		//Invalid command
		else {
			cout << "Command \"" << cmdin << "\" not recognized" << endl;
		}
		cout << endl;
	}
	
	return 0;
}

void clearCString(char*& cmdin) {
	for (int i = 0; i < strlen(cmdin); i++) {
		cmdin[i] = (char)0;
	}
}