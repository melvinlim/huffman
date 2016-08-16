#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdint.h>
#include<strings.h>

#define NODE struct Node
#define ITEM struct Item

ITEM{
	int val;
	int freq;
};

NODE{
	NODE *parent;
	NODE *left;
	NODE *right;
	ITEM *item;
};

int *randomArray(int k,int n){
	int i;
	int *p;
	int *res=malloc(sizeof(int)*n);
	p=res;
	srand(time(0));
	for(i=0;i<n;i++){
		*p++ = random()%k;
	}
	return res;
}

NODE *createNode(){
	NODE *node=malloc(sizeof(NODE));
	node->parent=0;
	node->left=0;
	node->right=0;
	node->item=0;
	return node;
}

NODE *createItem(int val,int freq){
	NODE *node=createNode();
	ITEM *item=malloc(sizeof(ITEM));
	item->val=val;
	item->freq=freq;
	node->item=item;
	return node;
}

NODE *newTree(){
	NODE *ret=createNode();
	return ret;
}

void insert(NODE *tree,NODE *node){
}

void printItem(ITEM *item){
	printf("(%d,%d)",item->val,item->freq);
}

void printTree(NODE *r){	
	if(r==0)	return;
	printTree(r->left);
	printItem(r->item);
	printTree(r->right);
}

void print(NODE *r){
	printTree(r);
	printf("\n");
}

int main(int argc,char *argv[]){
	uint8_t *buf;
	int i,n;
	int *a;
	NODE *item;
	NODE *tree;
	tree=createItem(3,5);
	print(tree);
	item=createItem(4,5);
	insert(tree,item);
	n=10;
	a=randomArray(0xff,n);
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
}
