#include<stdio.h>
int main(){
    FILE *fprt;
    char file[100];
    scanf("%s", file);
    fprt=fopen(file,"r");
    if(fprt==NULL){
        perror("cant open");
    }
    char string1[200];
    if(fgets(string1, 100, fprt)!=NULL){
		printf("%s", string1);
	}
    return 0;
}