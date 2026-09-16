#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    bool* wait_for_child = malloc(sizeof(bool));
    *wait_for_child = true;
    int rc = fork();
    
    if (rc<0)
    {
        printf("fork failed\n");
        exit(1);
    }else if (rc==0)
    {
        printf("hello (pid:%d)\n", (int) getpid());
        *wait_for_child = false;
    }
    else
    {
        
        while (*wait_for_child)
        {
            printf("waiting for child ");
        }
        printf("goodbye (pid:%d)\n", (int) getpid());
    }
    free(wait_for_child);
    return 0;
}