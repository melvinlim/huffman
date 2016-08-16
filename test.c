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
	uint8_t buf;
	uint32_t table[0xff+1];
	int i,n;
	ITEM *a,*b,*c;
	NODE *node=0;

	HEAP *heap=newHeap(MAXHEAPSIZE);
/*	
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
*/
	if(argc==1){
		printf("usage: %s [file]\n",argv[0]);
		return 0;
	}
	int fd=open(argv[1],O_RDONLY);
//	printf("%d\n",fd);
	if(fd<0){
		printf("unable to open file: %s\n",argv[1]);
		return 0;
	}
	bzero(table,(4*(0xff+1)));
	while(read(fd,&buf,1)>0){
//		printf("%02x ",buf);
		table[buf]++;
	}
	printf("\n");
	for(i=0;i<=0xff;i++){
		if(table[i]>0){
			printf("%02x:%d\n",i,table[i]);
			insert(heap,i,table[i]);
		}
	}
	printf("\n");
	print(heap);
/*
	for(i=0;i<=0xff;i++){
		a=removeMin(heap);
		printItem(a);
		printf("\n");
//	print(heap);
	}
*/
	i=0;
	while(heap->size>=2){
		a=removeMin(heap);
		b=removeMin(heap);
		node=newTree(a,b);
		c=newItem(a,b,node);
		insertItem(heap,c);
//		free(a);
//		free(b);
//		printf("[%d]\n",i++);
//		printNode(node);
//		print(heap);
	}
	printNode(node);
	printEdges(node);
//	print(heap);
	return 0;
}
