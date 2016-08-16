#include<encode.h>

char *getCode(STACK *s){
	int i;
	char ch;
	char *code=malloc(sizeof(char)*MAXSTACKSIZE);
	bzero(code,MAXSTACKSIZE*sizeof(char));
	i=0;
	while(i<s->size){
		code[i]=s->items[i+1];
		i++;
	};
	code[i]=0;
	return code;
}

void procEdge(char **table,STACK *s,NODE *r){
	if(r->left){
		push(s,'L');
		procEdge(table,s,r->left);
	}else{
//		printf("%s\n",getCode(s));
		table[r->item->val]=getCode(s);
		printf("%s\n",table[r->item->val]);
	}
	if(r->right){
		push(s,'R');
		procEdge(table,s,r->right);
	}
	pop(s);
}

char **getCodes(NODE *r){
	if(r==0)	return;
	char **table=malloc(sizeof(char *)*MAXHEAPSIZE);
	STACK *s=newStack();
//	printEdge(s,r);
	procEdge(table,s,r);
	free(s->items);
	free(s);
	return table;
}

void printEdge(STACK *s,NODE *r){
	if(r->left){
		push(s,'L');
		printEdge(s,r->left);
	}else{
		printItem(r->item);
		printStack(s);
	}
	if(r->right){
		push(s,'R');
		printEdge(s,r->right);
	}
	pop(s);
}

void printCodes(NODE *r){
	if(r==0)	return;
	STACK *s=newStack();
	printEdge(s,r);
	free(s->items);
	free(s);
}
