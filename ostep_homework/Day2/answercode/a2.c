#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int 
main(int argc, char *argv[])
{
    int fd = open("a2test.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    int rc = fork();
    if (rc < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (rc == 0) {
        write(fd, "hello from child\n", 17);
    } else {
        write(fd, "hello from parent\n", 18);
    }
    close(fd);
    return 0;
}