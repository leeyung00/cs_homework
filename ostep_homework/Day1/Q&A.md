### 1. 다음과 같이 플래그를 지정하고 프로그램을 실행시키시오 : ./process-run.py -l 5:100, 5:100. CPU 이용률은 얼마가 되어야 하는가 (예, CPU 가 사용 중인 시간의 퍼센트?) 그러한 이용률을 예측한 이유는 무엇인가? -c 플래그를 지정하여 예측이 맞는지 확인하시오.
A. 100%라고 생각한다. 두 개의 프로세스 모두 입출력 없이 cpu만 사용하기 때문이다.   

``` 
R. lee@lee:~/Desktop/ostep_homework$ ./process-run.py -l 5:100,5:100 -c

Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2        RUN:cpu         READY             1          
  3        RUN:cpu         READY             1          
  4        RUN:cpu         READY             1          
  5        RUN:cpu         READY             1          
  6           DONE       RUN:cpu             1          
  7           DONE       RUN:cpu             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
 10           DONE       RUN:cpu             1          
```

### 2. 이제 다음과 같이 플래그를 지정하고 실행시키시오 : ./process-run.py -l 4:100, 1:0. 이 플래그는 4 개의 명령어를 실행하고 모두 CPU 만 사용하는 하나의 프로세스와 오직 입출력을 요청하고 완료되기를 기다리는 하나의 프로세스를 명시한다. 두 프로세스가 모두 종료되는 데 얼마의 시간이 걸리는가? -c 플래그를 사용하여 예측한 것이 맞는지 확인하시오.

A. 우선 cpu를 사용하는 첫 번째 프로세스의 실행으로 인해 4의 시간이 걸리고 이후 입출력을 요청하는 프로세스에서 디폴트 값인 5의 시간과 IO를 시작하기 위한 시간과 종료하기 위한 시간이 추가로 필요함으로 2의 시간이 추가로 소용된다. 그렇기에 11의 시간이 걸릴 것이다.

```
lee@lee:~/Desktop/ostep_homework/Day1$ ./process-run.py -l 4:100,1:0 -c
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2        RUN:cpu         READY             1          
  3        RUN:cpu         READY             1          
  4        RUN:cpu         READY             1          
  5           DONE        RUN:io             1          
  6           DONE       BLOCKED                           1
  7           DONE       BLOCKED                           1
  8           DONE       BLOCKED                           1
  9           DONE       BLOCKED                           1
 10           DONE       BLOCKED                           1
 11*          DONE   RUN:io_done             1          
 ```