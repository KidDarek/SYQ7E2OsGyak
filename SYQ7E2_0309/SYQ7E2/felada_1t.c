#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(){
	char com[1000];
	int status;

	printf("Adjon meg egy parancsot: ");
	scanf("%s", com);
	do{
		status=system(com);
		if(WIFEXITED(status)) printf("Normalis befejezodes, visszaadott ertek: %d\n", WEXITSTATUS(status));
		printf("Adja meg a parancsot (kilepeshez Q): ");
		scanf("%s", com);
	} while(strcmp(com, "Q") !=0);
	exit(0);
}

