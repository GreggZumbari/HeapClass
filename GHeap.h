//GHeap.h
/*
This object is a tree of integers, starting with a single parent node. Each node branches off to two (2) other nodes, and could go on indefinetly (or at least while it hasn't run out of allocated memory).
By the way, when I say node, I'm not referring to a struct or anything like that. I'm referring to a single element in the tree, which as you can see, is an int array.
The algorithm for this int array, shown to me by Mr. Galbraith, is such that a parent's two children each reside at (parent's address * 2) and (parent's address * 2 + 1). For example, 4's children are at 8 and 9, and 9's children are at 18 and 19, etc. This works out so that nobody overrides anybody else, and it only uses a single array as storage.

int getHighest() - Returns the highest address of a token that been initialized
int getParent(int) - Returns the value at an address.
int getChild1(int) - Returns the first child of a parent.
int getChild2 (int) - Returns the second child of a parent
bool isEmpty(int) - Returns true if the address does not contain a value
void setParent(int, int) - Sets the value at the address of the first int to be the value of the second int. This should only be needed for the first value, which isn't a child of anything.
void setChild1(int, int) - Sets the first child of the address at the first int to be the value of the second int.
void setChild2(int, int) - Sets the second child of the address at the first int to be the value of the second int.

@author Greggory Hickman, February 2020
@version 1.0
 */
 
#include <iostream>

using namespace std;

class GHeap {
	public:
		//Constructor & Destructor
		GHeap(int);
		~GHeap();
		
		//Functions
		int getHighest();
		int getParent(int);
		int getChild1(int);
		int getChild2(int);
		bool isEmpty(int);
		void setParent(int, int);
		void setChild1(int, int);
		void setChild2(int, int);
		
	private:
		int highest;
		int LENGTH;
		int* heap;
};