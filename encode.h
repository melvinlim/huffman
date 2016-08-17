#include<string.h>
#include<heap.h>
#include<stack.h>

char *getCode(STACK *s);
void procEdge(char **table,STACK *s,NODE *r);
char **getCodes(NODE *r);
void printEdge(STACK *s,NODE *r);
void printCodes(NODE *r);
uint32_t *encodeArray(char **table,uint32_t *a,int n);
uint8_t *decodeArray(NODE *node,uint32_t *a);

NODE *encodeFile(NODE *node,char *input,char *output);
void decodeFile(NODE *node,char *input,char *output);
