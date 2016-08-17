#include<string.h>
#include<heap.h>
#include<stack.h>

char *getCode(STACK *s);
void procEdge(char **table,STACK *s,NODE *r);
char **getCodes(NODE *r);
void printEdge(STACK *s,NODE *r);
void printCodes(NODE *r);
uint32_t *encodeArray(char **table,uint32_t *a,int n);
void decodeArray(NODE *node,uint32_t *a);
