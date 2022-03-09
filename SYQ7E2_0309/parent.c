
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    if((pid = fork()<0))
    {
        perror("fork error");
    }
    else if(pid == 0)
    {
        if(excel("./child.out", "child", (char*) NULL)<0)
        {
            perror("execl error");
        }
    }
    exit(0);
}
