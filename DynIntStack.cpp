#include <iostream>
#include "Stack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
Stack::Stack(){
	top = NULL; 
	cap=0;
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void Stack::push(int num,int num2){
	StackNode *newNode;
	cap++;
	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->coor.x = num;
	newNode->coor.y = num2;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty()){
		top = newNode;
		newNode->next = NULL;
	}
    else{	// Otherwise, insert NewNode before top
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void Stack::pop(int &num,int &num2){
	StackNode *temp;

	if (isEmpty()){
		cout << "The stack is empty.\n";
	}
    else{	// pop value off top of stack
		if (cap==0)
		{
			top=nullptr;
		}
		num = top->coor.x;
		num2 = top->coor.y;
		temp = top->next;
		delete top;
		top = temp;
		cap--;

		
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool Stack::isEmpty(void) const{
	return top==NULL;
}

const Stack& Stack::operator<<(Point &p)
{
	push(p.x,p.y);
	return *this;
}

const Stack&  Stack::operator>>(Point &p)
{
	pop(p.x,p.y);
	return *this;
}