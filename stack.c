#include<stack.h>
STACK *newStack(){
	STACK *s=malloc(sizeof(STACK));
	s->items=malloc(sizeof(SITEM)*MAXSTACKSIZE);
	s->size=0;
	return s;
}
void push(STACK *s,SITEM item){
	s->items[++s->size]=item;
}
SITEM pop(STACK *s){
	if(s->size==0){
		return 0;
	}
	s->size--;
	return s->items[s->size+1];
}
SITEM top(STACK *s){
	return s->items[s->size];
}
