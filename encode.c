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

uint32_t *encodeArray(char **table,uint32_t *a,int n){
	uint32_t *cipherText=malloc(4*4096);
	char *str;
	int j,k,t;
	int i=0;
	t=0;
	bzero(cipherText,(4*4096));
	for(j=0;j<n;j++){
		str=table[a[j]];
		for(k=0;k<strlen(str);k++){
//			printf("%c",str[k]);
			if(t%32 == 0){
				i++;
			}
			if(str[k]=='R'){
				cipherText[i]=cipherText[i]+(1<<(t%32));
			}
//printf("\n%d:%x\n",t,cipherText[i]);
			t++;
		}
		printf("\n");
	}
	cipherText[0]=t;
	return cipherText;
}
/*
	for(j=n-1;j>=0;j--){
		str=table[a[j]];
		printf("%s\n",str);
		//for(k=0;k<strlen(str);k++){
		for(k=strlen(str)-1;k>=0;k--){
			printf("%c",str[k]);
			if(t%32 == 0){
				i++;
			}
			cipherText[i]=cipherText[i]<<1;
			if(str[k]=='R'){
				cipherText[i]+=1;
			}
printf("\n%d:%x\n",t,cipherText[i]);
			t++;
		}
		printf("\n");
	}
	cipherText[0]=t;
	return cipherText;
}
*/

void decodeArray(NODE *r,uint32_t *a){
	NODE *p=r;
	int i,j=0;
	uint32_t tmp;
	uint32_t bits=a[0];
printf("bits=%x\n",bits);
	for(i=0;i<bits;i++){
		if(i%32==0){
			j++;
			tmp=a[j];
		}
		if(p->left==0){
			//ans[k++]=p->item.val;
			//printf("%d ",p->item->val);
			printf("[%d]\n",p->item->val);
			p=r;
		}else if(p->right==0){
//printf("error\n");
		}
		if((tmp&1)==0){
//printf("l");
			p=p->left;
		}else{
//printf("r");
			p=p->right;
		}
		tmp=tmp>>1;
	}
	printf("[%d]\n",p->item->val);
	//printf("%d ",p->item->val);
	printf("\n");
}

void decodeFile(NODE *node,char *input,char *output){
	uint32_t *p;
	uint32_t n;
	int fd;
	int fo;
	uint32_t *array;
	if(output==0){
		output="output-cleartext\0";
	}
	fd=open(input,O_RDONLY);
	if(fd<0){
		printf("unable to open file: %s\n",input);
		return;
	}
	read(fd,&n,4);
printf("n=%lx\n",n);
	array=malloc(n*4);
	array[0]=n;
	p=array+1;
	while(read(fd,p,4)>0){
		p++;
	}
int i;
for(i=0;i<n;i++){
	if(array[i])
		printf("%x\n",array[i]);
}
	decodeArray(node,array);
}

NODE *encodeFile(NODE *node,char *input,char *output){
	int n,i;
	int fd;
	int fo;
	uint8_t buf;
	uint32_t *array,freqTable[0xff+1];
	ITEM *a,*b,*c;
//	NODE *node=0;

	if(output==0){
		output="output-ciphertext\0";
	}
	HEAP *heap=newHeap(MAXHEAPSIZE);
	fd=open(input,O_RDONLY);
	if(fd<0){
		printf("unable to open file: %s\n",input);
		return;
	}
	bzero(freqTable,(4*(0xff+1)));
	n=0;
	while(read(fd,&buf,1)>0){
//		printf("%02x ",buf);
		freqTable[buf]++;
		n++;
	}
//	printf("\n");
	for(i=0;i<=0xff;i++){
		if(freqTable[i]>0){
			printf("%02x:%ld\n",i,freqTable[i]);
			insert(heap,i,freqTable[i]);
		}
	}
	printf("\n");
	print(heap);
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
//	printNode(node);
//	printEdges(node);
//	print(heap);
//	printCodes(node);

	char **cTable;
	cTable=getCodes(node);
	for(i=0;i<=0xff;i++){
		if(cTable[i])
			printf("%i:%s\n",i,cTable[i]);
	}
	printf("\n");

	lseek(fd,0,SEEK_SET);
	array=malloc(n*sizeof(uint32_t));
	i=0;
	while(read(fd,&buf,1)>0){
		array[i++]=(uint32_t)buf;
		printf("%02x ",buf);
	}
	printf("\n");
#include<errno.h>
	uint32_t *tmpA;
	tmpA=encodeArray(cTable,array,i);
//printf("%d tmpA[0]\n");
	for(i=1;i<tmpA[0]/32+2;i++){
		printf("tmpA[%d]=0x%x\n",i,tmpA[i]);
	}
//	decodeArray(node,tmpA);
//	fo=open(output,O_WRONLY|O_CREAT|O_TRUNC|S_IRWXU|S_IRWXG|S_IRWXO);
	fo=creat(output,O_WRONLY);
	printf("fo=%d\n",fo);
	array=tmpA;
int ret;
	for(i=0;i<tmpA[0]/32+2;i++){
		ret=write(fo,array,4);
		if(ret<0){
			printf("error: %d\n",errno);
			perror(0);
			return 0;
		}
		printf("ret=%d\n",ret);
//		printf("tmpA[%d]=0x%x\n",i,tmpA[i]);
		printf("tmpA[%d]=0x%x\n",i,*array);
		array++;
	}
	close(fo);
	return node;
}

/*
	if(argc==1){
		printf("usage: %s [file]\n",argv[0]);
		return 0;
	}
*/
