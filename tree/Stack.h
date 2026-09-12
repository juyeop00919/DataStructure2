#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int stackElement;

typedef struct arrayStack {
	stackElement* data;
	int top;
	int size;
} ArrayStack;

extern ArrayStack* createArrayStack(int size);
//extern int destroyArrayStack(ArrayStack* s); 
extern int pushArrayStack(ArrayStack* s, stackElement item);
extern stackElement popArrayStack(ArrayStack* s);
//extern stackElement peekStack(ArrayStack* s);
extern int printArrayStack(ArrayStack* s);
extern int emptyArrayStack(ArrayStack* s);
extern int fullArrayStack(ArrayStack* s);

//dd