#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdint.h>
#include<strings.h>

#define MAXHEAPSIZE 512

#define HEAP struct Heap
#define ITEM struct Item
#define NODE struct Node

#define PARENT(x) (x/2)
#define LEFT(x) (x*2)
#define RIGHT(x) (x*2+1)

ITEM{
	int val;
	int freq;
	NODE *node;
};

HEAP{
	int size;
	ITEM *items;
};

NODE{
	NODE *parent;
	NODE *left;
	NODE *right;
	ITEM *item;
};

HEAP *newHeap(int n);
void swap(ITEM *a,int x,int y);
void heapify(HEAP *heap,int pos);
void insert(HEAP *heap,int val,int freq);
void printItem(ITEM *item);
void printHeap(HEAP *r);
void print(HEAP *r);
ITEM *removeMin(HEAP *heap);
void heapDown(HEAP *heap,int pos);

void insertItem(HEAP *heap,ITEM *item);
ITEM *newItem(ITEM *a,ITEM *b,NODE *node);

NODE *createNode(ITEM *a);
NODE *newTree(ITEM *a,ITEM *b);
void printTree(NODE *r);
void printNode(NODE *r);
void printEdges(NODE *r);
