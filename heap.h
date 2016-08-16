#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdint.h>
#include<strings.h>

#define MAXHEAPSIZE 512

#define HEAP struct Heap
#define ITEM struct Item

#define PARENT(x) (x/2)
#define LEFT(x) (x*2)
#define RIGHT(x) (x*2+1)

ITEM{
	int val;
	int freq;
};

HEAP{
	int size;
	ITEM *items;
};

HEAP *newHeap(int n);
void swap(ITEM *a,int x,int y);
void heapify(HEAP *heap,int pos);
void insert(HEAP *heap,int val,int freq);
void printItem(ITEM *item);
void printHeap(HEAP *r);
void print(HEAP *r);
