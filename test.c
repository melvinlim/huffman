#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdint.h>
#include<strings.h>

#include<heap.h>

ITEM *randomItems(int k,int maxf,int n){
	int i;
	ITEM *p;
	ITEM *res=malloc(sizeof(ITEM)*n);
	p=res;
	srand(time(0));
	for(i=0;i<n;i++){
		(*p).val	= random()%k;
		(*p).freq	= random()%maxf;
		p++;
	}
	return res;
}

void randomInserts(HEAP *heap,int n){
	int i;
	for(i=0;i<n;i++){
		insert(heap,random()%0xff,random()%20);
	}
}

int main(int argc,char *argv[]){
	uint8_t *buf;
	int i,n;
	ITEM *a;

	HEAP *heap=newHeap(MAXHEAPSIZE);
	
	insert(heap,3,5);
	insert(heap,4,4);
	print(heap);
	swap(heap->items,1,2);
	print(heap);
	swap(heap->items,2,1);
	print(heap);
	randomInserts(heap,20);
	print(heap);
	n=10;
	a=randomItems(0xff,25,n);
	for(i=0;i<n;i++){
		printItem(&a[i]);
	}
	printf("\n");
	return 0;
}
