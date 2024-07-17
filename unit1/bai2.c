#include<stdio.h>
int main(){
 	FILE *fprt;	
	fprt=fopen("bai2.txt","r");
	if (fprt==NULL){
		perror("no file");
	}
	char string1[100];
	if(fgets(string1, 100, fprt)!=NULL){
		printf("%s", string1);
	}
	fclose(fprt);
	return 0;
}
