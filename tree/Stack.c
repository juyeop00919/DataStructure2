#include "Stack.h"


ArrayStack* createArrayStack(int size) {
	ArrayStack* re = (ArrayStack*)malloc(sizeof(ArrayStack));
	re->data = (stackElement*)malloc(sizeof(stackElement) * size);
	re->top = -1;
	re->size = size;
	return re;
}
int emptyArrayStack(ArrayStack* s) {
	return s->top == -1;
}
int fullArrayStack(ArrayStack* s) {
	return s->top == s->size - 1;
}

int destroyArrayStack(ArrayStack* s) {
	if (s != NULL) {
		if (s->data != NULL) free(s->data);
		free(s);
	}
	return 1;
}


int pushArrayStack(ArrayStack* s, stackElement item) {
	if (fullArrayStack(s)) {
		return 0;
	}
	s->top++;
	s->data[s->top] = item;
	//s->size++;
	return 1;
}


stackElement popArrayStack(ArrayStack* s) {
	if (emptyArrayStack(s)) {
		return (stackElement)NULL;
	}
	stackElement temp = s->data[s->top];
	s->top--;
	//s->size--;
	return temp;
}
stackElement peekArrayStack(ArrayStack* s) {
	if (emptyArrayStack(s)) return (stackElement)0;
	return s->data[s->top];
}
int printArrayStack(ArrayStack* s) {
	printf("Stack : \n");
	printf("Size : %d , Top %d\n", s->size, s->top);
	for (int i = 0; i <= s->top; i++)
	{
		printf("[%d] %c\n", i, s->data[i]);
	}
}