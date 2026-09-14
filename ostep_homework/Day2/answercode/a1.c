#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int x = 100;
    int rc = fork();
    if (rc<0)
    {
        printf("fork failed\n");
        exit(1);
    }
    else if (rc==0)
    {
        printf("hello, I am child (pid:%d), (x:%d)\n", (int) getpid(), x);
        printf("child: x=%d\n", ++x);
    }
    else
    {
        printf("hello, I am parent of %d (pid:%d), (x:%d)\n",
           rc, (int) getpid(), x);
        printf("parent: x=%d\n", --x);
    }
    return 0;
}