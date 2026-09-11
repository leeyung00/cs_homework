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

### 3. 옵션으로 지정된 프로세스의 순서를 바꾸시오:./process-run.py -l 1:0, 4:100.이제 어떤 결과가 나오는가?실행 순서를 교환하는 것은 중요한가?이유는 무엇인가? (언제나처럼 -c 플래그를 사용하여 예측이 맞는지 확인하시오.)

A. 순서를 교환하는 것은 중요하다. 왜냐하면 IO가 작동하는 동안 놀고 있던 cpu가 작동하여 기존 작업을 더 빠르게 끝내기 때문이다.

'''
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -l 1:0,4:100 -c
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7*   RUN:io_done          DONE             1 
  ''''

### 4. 중요한 플래그 중 하나는 -S로서 프로세스가 입출력을 요청했을 때 시스템이 어떻게 반응하는지를 결정한다.이 플래그가SWITCH_ON_END로 지정되면 시스템은 요청 프로세스가 입출력을 하는 동안 다른프로세스로 전환하지 않고 대신 요청 프로세스가 종료될 때까지 기다린다.입출력만수행하는 프로세스와 CPU 작만 하는 프로세스 두 발를 실행시키면 어떤 결과가 발생하는가?(-l 1:0,4:200 -c -S SWITCH_ON_END)

A. 교환이 되지 않기 때문에 2번 상황과 같이 cpu가 노는 시간이 발생하여 오랜 시간이 걸린다.

'''
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -l 1:0,4:200 -c -S SWITCH_ON_END
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
 10           DONE       RUN:cpu             1          
 11           DONE       RUN:cpu             1  
'''

### 5. 이번에는 프로세스가 입출력을 기다릴 때마다 다른 프로세스로 전환하도록 플래그를 지정하여 같은 프로세스를실행시켜보자(-l 1:0,4:100 -c -S SWITCH_ON_IO). 이제 어떤 결과가 생하는가?-c를 사용하여 예측이 맞는지 확인하시오

A. 문맥 교환이 발생하여 cpu가 노는 시간 없이 작업을 완료해 빠른 시간에 종료되었다.

'''
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -l 1:0,4:200 -c -S SWITCH_ON_IO
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7*   RUN:io_done          DONE             1 
'''

### 6. 또 다른 중요한 행동은 입출력이 완료되을때무을하느냐이다.-I IO_RUN_LATER가 지정되면 입출력이 완료되을 때 입출력을 요청한 프로세스가 로 실행될 필요가다.완료 시점에 실행 중이던 프로세스가 계속 실행된다.다음과 같은 조합의 프로세스를 실행시키면 무슨 결과가 나오는가?(./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p)시스템 자원은 효과적으로 활용되는

A. IO작업이 되는 동안 cpu를 활용하여 17까지는 적절해 보였지만 이루 IO작업으로 인해 시간이 비효율적으로 소모된다.

'''
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1          
  8          READY          DONE       RUN:cpu         READY             1          
  9          READY          DONE       RUN:cpu         READY             1          
 10          READY          DONE       RUN:cpu         READY             1          
 11          READY          DONE       RUN:cpu         READY             1          
 12          READY          DONE          DONE       RUN:cpu             1          
 13          READY          DONE          DONE       RUN:cpu             1          
 14          READY          DONE          DONE       RUN:cpu             1          
 15          READY          DONE          DONE       RUN:cpu             1          
 16          READY          DONE          DONE       RUN:cpu             1          
 17    RUN:io_done          DONE          DONE          DONE             1          
 18         RUN:io          DONE          DONE          DONE             1          
 19        BLOCKED          DONE          DONE          DONE                           1
 20        BLOCKED          DONE          DONE          DONE                           1
 21        BLOCKED          DONE          DONE          DONE                           1
 22        BLOCKED          DONE          DONE          DONE                           1
 23        BLOCKED          DONE          DONE          DONE                           1
 24*   RUN:io_done          DONE          DONE          DONE             1          
 25         RUN:io          DONE          DONE          DONE             1          
 26        BLOCKED          DONE          DONE          DONE                           1
 27        BLOCKED          DONE          DONE          DONE                           1
 28        BLOCKED          DONE          DONE          DONE                           1
 29        BLOCKED          DONE          DONE          DONE                           1
 30        BLOCKED          DONE          DONE          DONE                           1
 31*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)
'''

### 7. 같은 프로세스 조합을 실행시킬 때 -I IO_RUN_IMMEDIATE를 지정하고 실행시키시오.이 플래그는 입출력이 완료되을 때 요청 프로세스가 곧로 실행되는 동작을 의미한다.이 동작은 어떤 결과를 만들어 내는가?방금 입출력을 완료한 프로세스를 다시 실행시키는 것이 좋은 생각일 수 있는 이유는 무인가?

A. IO 작업을 하는 와중에 CPU는 노는 시간이 발생한다 그렇기에 이 시간에 다른 작업을 한다면 시간을 더욱 효율적으로 사용 가능하기 때문이다.

'''
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1          
  8         RUN:io          DONE         READY         READY             1          
  9        BLOCKED          DONE       RUN:cpu         READY             1             1
 10        BLOCKED          DONE       RUN:cpu         READY             1             1
 11        BLOCKED          DONE       RUN:cpu         READY             1             1
 12        BLOCKED          DONE       RUN:cpu         READY             1             1
 13        BLOCKED          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1          
 15         RUN:io          DONE          DONE         READY             1          
 16        BLOCKED          DONE          DONE       RUN:cpu             1             1
 17        BLOCKED          DONE          DONE       RUN:cpu             1             1
 18        BLOCKED          DONE          DONE       RUN:cpu             1             1
 19        BLOCKED          DONE          DONE       RUN:cpu             1             1
 20        BLOCKED          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 21
Stats: CPU Busy 21 (100.00%)
Stats: IO Busy  15 (71.43%)
'''

### 8. 이제 다음과 같이 무작위로 생성된 프로세스를 실행시켜 보자.예를 들면,-s 1 -l 3:50,3:50,-s 2 -l 3:50,3:50,-s 3 -l 3:50,3:50.어떤 양상을 보일지 예측할 수 있는지 생각해 보시오.-I IO_RUN_IMMEDIATE를 지정했을 때와 -I IO_RUN_LATER를 지정했을 때 어떤 결과가 나오는가?-S SWITCH_ON_IO 대 -S SWITCH_ON_END의 경우에는 어떤 결과가 나오는가

A. -I IO_RUN_IMMEDIATE -S SWITCH_ON_IO인 경우가 가장 효율적일 것이다. IO가 실행되는 동안에는 cpu를 사용할 수 있기 때문에 IO가 필요한 순간 빠르게 IO작업을 위해 cpu 1을 할당하고 남는 시간에 cpu를 돌리면 가장 효율적으로 관리할 수 있기 때문이다.

'''
i) -I IO_RUN_IMMEDIATE -S SWITCH_ON_END일 경우
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 1 -l 3:50,3:50 -I IO_RUN_IMMEDIATE -S SWITCH_ON_END -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1          
  9         RUN:io         READY             1          
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14        BLOCKED         READY                           1
 15*   RUN:io_done         READY             1          
 16           DONE       RUN:cpu             1          
 17           DONE       RUN:cpu             1          
 18           DONE       RUN:cpu             1          

Stats: Total Time 18
Stats: CPU Busy 8 (44.44%)
Stats: IO Busy  10 (55.56%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 2 -l 3:50,3:50 -I IO_RUN_IMMEDIATE -S SWITCH_ON_END -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1          
  8         RUN:io         READY             1          
  9        BLOCKED         READY                           1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14*   RUN:io_done         READY             1          
 15        RUN:cpu         READY             1          
 16           DONE       RUN:cpu             1          
 17           DONE        RUN:io             1          
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1          
 24           DONE        RUN:io             1          
 25           DONE       BLOCKED                           1
 26           DONE       BLOCKED                           1
 27           DONE       BLOCKED                           1
 28           DONE       BLOCKED                           1
 29           DONE       BLOCKED                           1
 30*          DONE   RUN:io_done             1          

Stats: Total Time 30
Stats: CPU Busy 10 (33.33%)
Stats: IO Busy  20 (66.67%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 3 -l 3:50,3:50 -I IO_RUN_IMMEDIATE -S SWITCH_ON_END -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1          
  9        RUN:cpu         READY             1          
 10           DONE        RUN:io             1          
 11           DONE       BLOCKED                           1
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16*          DONE   RUN:io_done             1          
 17           DONE        RUN:io             1          
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1          
 24           DONE       RUN:cpu             1          

Stats: Total Time 24
Stats: CPU Busy 9 (37.50%)
Stats: IO Busy  15 (62.50%)

ii) -I IO_RUN_IMMEDIATE -S SWITCH_ON_IO일 경우
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 1 -l 3:50,3:50 -I IO_RUN_IMMEDIATE -S SWITCH_ON_IO -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1          
  9         RUN:io          DONE             1          
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1          

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 2 -l 3:50,3:50 -I IO_RUN_IMMEDIATE -S SWITCH_ON_IO -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7*   RUN:io_done       BLOCKED             1             1
  8         RUN:io       BLOCKED             1             1
  9*       BLOCKED   RUN:io_done             1             1
 10        BLOCKED        RUN:io             1             1
 11        BLOCKED       BLOCKED                           2
 12        BLOCKED       BLOCKED                           2
 13        BLOCKED       BLOCKED                           2
 14*   RUN:io_done       BLOCKED             1             1
 15        RUN:cpu       BLOCKED             1             1
 16*          DONE   RUN:io_done             1          

Stats: Total Time 16
Stats: CPU Busy 10 (62.50%)
Stats: IO Busy  14 (87.50%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 3 -l 3:50,3:50 -I IO_RUN_IMMEDIATE -S SWITCH_ON_IO -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7        BLOCKED       BLOCKED                           2
  8*   RUN:io_done       BLOCKED             1             1
  9*         READY   RUN:io_done             1          
 10          READY        RUN:io             1          
 11        RUN:cpu       BLOCKED             1             1
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16*          DONE   RUN:io_done             1          
 17           DONE       RUN:cpu             1          

Stats: Total Time 17
Stats: CPU Busy 9 (52.94%)
Stats: IO Busy  11 (64.71%)

iii)-I IO_RUN_LATER -S SWITCH_ON_END일 경우
ee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 1 -l 3:50,3:50 -I IO_RUN_LATER -S SWITCH_ON_END -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1          
  9         RUN:io         READY             1          
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14        BLOCKED         READY                           1
 15*   RUN:io_done         READY             1          
 16           DONE       RUN:cpu             1          
 17           DONE       RUN:cpu             1          
 18           DONE       RUN:cpu             1          

Stats: Total Time 18
Stats: CPU Busy 8 (44.44%)
Stats: IO Busy  10 (55.56%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 2 -l 3:50,3:50 -I IO_RUN_LATER -S SWITCH_ON_END -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1          
  8         RUN:io         READY             1          
  9        BLOCKED         READY                           1
 10        BLOCKED         READY                           1
 11        BLOCKED         READY                           1
 12        BLOCKED         READY                           1
 13        BLOCKED         READY                           1
 14*   RUN:io_done         READY             1          
 15        RUN:cpu         READY             1          
 16           DONE       RUN:cpu             1          
 17           DONE        RUN:io             1          
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1          
 24           DONE        RUN:io             1          
 25           DONE       BLOCKED                           1
 26           DONE       BLOCKED                           1
 27           DONE       BLOCKED                           1
 28           DONE       BLOCKED                           1
 29           DONE       BLOCKED                           1
 30*          DONE   RUN:io_done             1          

Stats: Total Time 30
Stats: CPU Busy 10 (33.33%)
Stats: IO Busy  20 (66.67%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 3 -l 3:50,3:50 -I IO_RUN_LATER -S SWITCH_ON_END -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7        BLOCKED         READY                           1
  8*   RUN:io_done         READY             1          
  9        RUN:cpu         READY             1          
 10           DONE        RUN:io             1          
 11           DONE       BLOCKED                           1
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16*          DONE   RUN:io_done             1          
 17           DONE        RUN:io             1          
 18           DONE       BLOCKED                           1
 19           DONE       BLOCKED                           1
 20           DONE       BLOCKED                           1
 21           DONE       BLOCKED                           1
 22           DONE       BLOCKED                           1
 23*          DONE   RUN:io_done             1          
 24           DONE       RUN:cpu             1          

Stats: Total Time 24
Stats: CPU Busy 9 (37.50%)
Stats: IO Busy  15 (62.50%)

iv) -I IO_RUN_LATER -S SWITCH_ON_IO일 경우
lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 1 -l 3:50,3:50 -I IO_RUN_LATER -S SWITCH_ON_IO -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1          
  9         RUN:io          DONE             1          
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1          

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 2 -l 3:50,3:50 -I IO_RUN_LATER -S SWITCH_ON_IO -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7*   RUN:io_done       BLOCKED             1             1
  8         RUN:io       BLOCKED             1             1
  9*       BLOCKED   RUN:io_done             1             1
 10        BLOCKED        RUN:io             1             1
 11        BLOCKED       BLOCKED                           2
 12        BLOCKED       BLOCKED                           2
 13        BLOCKED       BLOCKED                           2
 14*   RUN:io_done       BLOCKED             1             1
 15        RUN:cpu       BLOCKED             1             1
 16*          DONE   RUN:io_done             1          

Stats: Total Time 16
Stats: CPU Busy 10 (62.50%)
Stats: IO Busy  14 (87.50%)

lee@lee:~/Desktop/cs_homework/ostep_homework/Day1$ ./process-run.py -s 3 -l 3:50,3:50 -I IO_RUN_LATER -S SWITCH_ON_IO -c -p
Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7        BLOCKED       BLOCKED                           2
  8*   RUN:io_done       BLOCKED             1             1
  9*       RUN:cpu         READY             1          
 10           DONE   RUN:io_done             1          
 11           DONE        RUN:io             1          
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16           DONE       BLOCKED                           1
 17*          DONE   RUN:io_done             1          
 18           DONE       RUN:cpu             1          

Stats: Total Time 18
Stats: CPU Busy 9 (50.00%)
Stats: IO Busy  11 (61.11%)
'''