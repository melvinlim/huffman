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

void insert(HEAP *heap,int val,int freq){
	ITEM *p=heap->items;
	heap->size++;
	p[heap->size].val=val;
	p[heap->size].freq=freq;
}

void printItem(ITEM *item){
	printf("(%d,%d)",item->val,item->freq);
}

void printHeap(HEAP *r){
	int i;
	ITEM *p=r->items+1;
	for(i=0;i<r->size;i++){
		printItem(p++);
	}
}

void print(HEAP *r){
	printHeap(r);
	printf("\n");
}

int main(int argc,char *argv[]){
	uint8_t *buf;
	int i,n;
	int *a;

	HEAP *heap=newHeap(MAXHEAPSIZE);
	
	insert(heap,3,5);
	insert(heap,4,4);
	print(heap);
	swap(heap->items,1,2);
	print(heap);
	n=10;
	a=randomArray(0xff,n);
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
}
