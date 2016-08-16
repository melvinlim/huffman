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

HEAP *newHeap(int n){
	HEAP *heap=malloc(sizeof(HEAP));
	heap->items=malloc(sizeof(ITEM)*(n+1));
	heap->size=0;
	return heap;
}

swap(ITEM *a,int x,int y){
	ITEM tmp;
	tmp=a[x];
	a[x]=a[y];
	a[y]=tmp;
}

void heapify(HEAP *heap,int pos){
	int minPos,minVal,size;
	int t;
	if(pos==0)	return;
	ITEM *a=heap->items;
	minPos=pos;
	minVal=a[pos].freq;
	size=heap->size;
	if(LEFT(pos)<=size){
		t=a[LEFT(pos)].freq;
		if(t<minVal){
			minVal=t;
			minPos=LEFT(pos);
		}
	}else{
		return heapify(heap,PARENT(pos));
	}
	if(RIGHT(pos)<=size){
		t=a[RIGHT(pos)].freq;
		if(t<minVal){
			minVal=t;
			minPos=RIGHT(pos);
		}
	}
	swap(a,pos,minPos);
	heapify(heap,PARENT(pos));
}

void heapDown(HEAP *heap,int pos){
	int t;
	int size;
	ITEM *a=heap->items;
	size=heap->size;
	if(LEFT(pos)>size){
		return;
	}
	if(RIGHT(pos)>size){
		if(a[LEFT(pos)].freq<=a[pos].freq){
			swap(a,pos,LEFT(pos));
			heapDown(heap,LEFT(pos));
		}
		return;
	}
	if(a[LEFT(pos)].freq<=a[RIGHT(pos)].freq){
		if(a[LEFT(pos)].freq<=a[pos].freq){
			swap(a,pos,LEFT(pos));
			heapDown(heap,LEFT(pos));
		}else{
			return;
		}
	}else{
		if(a[RIGHT(pos)].freq<=a[pos].freq){
			swap(a,pos,RIGHT(pos));
			heapDown(heap,RIGHT(pos));
		}else{
			return;
		}
	}
}

ITEM *removeMin(HEAP *heap){
	int size;
	ITEM *minItem=malloc(sizeof(ITEM));
	*minItem=heap->items[1];
	if(heap->size==0)	return 0;
	swap(heap->items,heap->size,1);
	heap->size--;
	size=heap->size;
	if(size==0)	return minItem;
	heapDown(heap,1);
	return minItem;
}

void insert(HEAP *heap,int val,int freq){
	ITEM *p=heap->items;
	heap->size++;
	p[heap->size].val=val;
	p[heap->size].freq=freq;
	heapify(heap,PARENT(heap->size));
}

void printItem(ITEM *item){
	printf("(%02x,%d)",item->val,item->freq);
}

void printHeap(HEAP *r){
	int i;
	ITEM *p=r->items+1;
	for(i=1;i<=r->size;i++){
		printf("%d:",i);
		printItem(p++);
		printf("\n");
	}
}

void print(HEAP *r){
	printHeap(r);
	printf("\n");
}
