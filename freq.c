#include<stdio.h>
#include<fcntl.h>
#include<stdint.h>
#include<strings.h>
int main(int argc,char *argv[]){
	uint8_t *buf;
	uint32_t i,table[0xff];
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
	bzero(table,(4*0xff));
	while(read(fd,buf,1)>0){
//		printf("%02x ",*buf);
		table[*buf]++;
	}
	printf("\n");
	for(i=0;i<0xff;i++){
		if(table[i]>0){
			printf("%02x:%d\n",i,table[i]);
		}
	}
	printf("\n");
}
