#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int status, status1;

	//ha letezik
	status=system("dir");
	if(status < 0) perror("system() error");
	if(WIFEXITED(status)) printf("Normalis befejezodes, visszaadott ertek: %d\n", WEXITSTATUS(status));
	else printf("Nem normalis befejezodes\n");
	
	//ha nem letezik
	status=system("theterminator");
	if(status < 0) perror("system() error");
	if(WIFEXITED(status)) printf("Normalis befejezodes, visszaadott ertek: %d\n ", WEXITSTATUS(status));
	else printf("Nem normalis befejezodes\n");
	exit(0);

}
