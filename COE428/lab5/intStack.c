/**
 *  The functions in this module implement a Stack data structure
 *  of integers.  (Note that chars are also integers so this
 *  integer Stack can be used for chars as well.)
 *
 *  NOTE: the stack is implemented as a fixed size array (size = 100).
 *  Consequently, no more than 100 integers can be pushed onto
 *  the Stack at any given time.
 */

// Implementation hints:
//   The 3 functions--push, pop and isEmpty--share information
//   about the array used to implement the stack and the index
//   of the "top" of the stack.
//
//   You may want to make these variables global...
//   ...but that would
//   be a mistake (because anyone using the module would have
//   to ensure that they did not use global variables with the
//   same names).
//
//   An alternative in C is a "static global".
//   If a global variable is qualified as "static", it is global only
//   within the source code file where it is declared.
//   In parituclar, it cannot conflict with any other global variable.
//
//  RECOMMENDATION:
//   Uncomment the following 2 lines and use these static globals!
#include <stdio.h>
#include <stdlib.h>
#include "intStack.h"
static int top = 0;
static int stack[100];


/**
 * pop() removes the top integer on the stack and returns it.
 *
 * If pop() is attempted on an empty stack, an error message
 * is printed to stderr and the value -1 (minus one) is returned.
 */

int pop2()
{
	if(isEmpty2()){
		fprintf(stderr, "Stack is empty\n");
		return -1;
	}
	top--;
	return stack[top];
}

/**
 *  push(thing2push) adds the "thing2push" to the top of the stack.
 *
 *  If there is no more space available on the Stack, an error
 *  message is printed to stderr.
 */
void push2(int thing2push)
{
	if(top >= 100-1){
		fprintf(stderr, "Stack Overflow");
		return;
	}
	
	stack[top]= thing2push;
	top++;

	printf("Pushed: %d\n", thing2push);	
}

/**
 * isEmpty() returns a non-zero integer (not necessarily 1) if the
 * stack is empty; otherwise, it returns 0 (zero).
 *
 */
int isEmpty2()
{
		return top == 0;
}

void printStack(){
	for(int i=0; i<=top; i++){
		printf("%d", stack[i]);
	}
}

