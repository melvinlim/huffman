#include<string.h>
#include<heap.h>
#include<stack.h>

char *getCode(STACK *s);
void procEdge(char **table,STACK *s,NODE *r);
char **getCodes(NODE *r);
void printEdge(STACK *s,NODE *r);
void printCodes(NODE *r);
uint32_t *encodeArray(char **table,int *a,int n);
