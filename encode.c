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
	int bits=a[0];
	for(i=0;i<bits;i++){
		if(i%32==0){
			j++;
			tmp=a[j];
		}
		if(p->left==0){
			//ans[k++]=p->item.val;
			//printf("%d ",p->item->val);
			printf("\n[%d]\n",p->item->val);
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
	printf("\n[%d]\n",p->item->val);
	//printf("%d ",p->item->val);
	printf("\n");
}
