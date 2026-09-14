## 1.fork()를 호출하는 프로그램을 작성하라.fork()를 호출하기 전에 메인 프로세스는 변수에 접근하고 (예,x)변수에 값을 지정하라 (예,100).자식 프로세스에서 그 변수의 값은 무인가?부모와 자식이 변수 x를 변경한 후에 변수는 어떻게 변했는가?
```
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
--------------------------------------------------------------------------------------------
lee@lee:~/Desktop/cs_homework/ostep_homework/Day2/answercode$ ./a1 
hello, I am parent of 7108 (pid:7107), (x:100)
parent: x=99
hello, I am child (pid:7108), (x:100)
child: x=101
```
변수 x는 각기 다른 주소를 가진다고 판단된다. 왜냐하면 부모 프로세스에서 값의 변화가 있었지만 자식 프로세스에서는 이 변화가 나타나지 않았기 때문이다.

## 2.open() 시스템 콜을 사용하여 파일을 여는 프로그램을 작성하고 새 프로세스를 생성하기 위하여 fork()를 호출하라.자식과 부모가 open()에 의해 반환된 파일 디스크립터에 접근할 수 있는가?부모와 자식 프로세스가 동시에 파일에 쓰기 작을 할 수 있는가?

```
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

--------------------------------------------------------------------------------
lee@lee:~/Desktop/cs_homework/ostep_homework/Day2/answercode$ cat a2test.txt 
hello from parent
hello from child
```
두 프로세스 모두 파일 디스크럽터에 접근이 가능하다. 두 프로세스의 write() 실행의 결과가 모두 나타나고 있기 때문이다.
이는 오프셋이 공유되어 가능한 기능이다. open() 시스템 콜을 호출하고 fork()를 통해 자식프로세스를 만들면 두 프로세스는 같은 파일에 대해 같은 오프셋을 공유한다. 그렇기에 같은 파일을 읽고 순차적으로 글을 쓰는 것이 가능하게 되었다

## 3.fork()를 사용하는 다른 프로그램을 작성하라.자식 프로세스는“hello”를 출력하고부모 프로세스는 “goodbye”를 출력해야 한다.항상 자식 프로세스가 먼저 출력하게 하라.부모가 wait()를 호출하지 않고 할 수 있는가?

## 4.fork()를 호출하고 /bin/ls를 실행하기 위하여 exec() 계열의 함수를 호출 하는 프로그램을 작성하라.exec()의 변형 execl(),execle(),execlp(),execv(),execvp(),execve() 모두를 사용할 수 있는지 시도해 보라.기본적으로는 동일한 기능을 수행하는 시스템 콜에 여러 변형이 있는 이유를 생각해 보라.

## 5.wait()를 사용하여 자식 프로세스가 종료되기를 기다리는 프로그램을 작성하라. wait()가 반환하는 것은 무인가?자식 프로세스가 wait()를 호출하면 어떤 결과가 발생하는가?