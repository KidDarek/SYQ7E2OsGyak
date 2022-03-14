#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t pid;
	if((pid=fork()) < 0)
		perror("fork error");
	else if(pid == 0){
		if(execlp("ls", "ls", (char*)NULL))
			perror("execl error");
	}
	if(waitpid(pid, NULL, 0) < 0)
		perror("wait error");
	else printf("Szulo megvarta a gyereket.\n");
	exit(0);
}
