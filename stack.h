#ifndef _STACK
#define _STACK

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#define MAXSTACKSIZE 64
#define STACK struct Stack

typedef char SITEM;

STACK{
	int size;
	SITEM *items;
};

void push(STACK *s,SITEM item);
SITEM pop(STACK *s);
SITEM top(STACK *s);
void printStack(STACK *s);
STACK *newStack();

#endif
