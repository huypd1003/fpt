#include <stdio.h>

int main() {
    int pid;
    scanf("%d",&pid);
    FILE *file;
    char name[256];
    sprintf(name,"/proc/%d/comm",pid);
    file = fopen(name, "r");
    if (file == NULL) {
        perror("Error opening /proc");
        return 1;
    }
	if(fgets(name, 256, file)!=NULL){
		printf("%s", name);
	}
    fclose(file);
    return 0;
}   
