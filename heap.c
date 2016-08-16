#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdint.h>
#include<strings.h>
#include<heap.h>

ITEM *newItem(ITEM *a,ITEM *b,NODE *node){
	ITEM *c=malloc(sizeof(ITEM));
	c->freq=a->freq+b->freq;
	c->val=a->val+b->val;
	c->node=node;
	return c;
}

NODE *createNode(ITEM *a){
	NODE *node=malloc(sizeof(NODE));
	node->parent=0;
	node->left=0;
	node->right=0;
	node->item=a;
	return node;
}

NODE *newTree(ITEM *a,ITEM *b){
	NODE *tree=createNode(0);
	if(a->node==0){
		tree->left=createNode(a);
	}else{
		tree->left=a->node;
	}
	if(b->node==0){
		tree->right=createNode(b);
	}else{
		tree->right=b->node;
	}
	return tree;
}

void printTree(NODE *r){	
	if(r==0)	return;
	printTree(r->left);
	if(r->item){
		printf("node->item:");
		printItem(r->item);
		printf("\n");
	}
	printTree(r->right);
}

void printNode(NODE *r){
	printf("tree:\n");
	printTree(r);
	printf("\n");
}

HEAP *newHeap(int n){
	HEAP *heap=malloc(sizeof(HEAP));
	heap->items=malloc(sizeof(ITEM)*(n+1));
	heap->size=0;
	return heap;
}

void swap(ITEM *a,int x,int y){
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

void insertItem(HEAP *heap,ITEM *item){
	ITEM *p=heap->items;
	heap->size++;
	p[heap->size].val=item->val;
	p[heap->size].freq=item->freq;
	p[heap->size].node=item->node;
	heapify(heap,PARENT(heap->size));
}

void insert(HEAP *heap,int val,int freq){
	ITEM *p=heap->items;
	heap->size++;
	p[heap->size].val=val;
	p[heap->size].freq=freq;
	p[heap->size].node=0;
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
printNode(p->node);
		printItem(p++);
		printf("\n");
	}
}

void print(HEAP *r){
	printHeap(r);
	printf("\n");
}
