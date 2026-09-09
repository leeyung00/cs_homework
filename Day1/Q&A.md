## 1. 다음과 같이 플래그를 지정하고 프로그램을 실행시키시오 : ./process-run.py -l 5:100, 5:100. CPU 이용률은 얼마가 되어야 하는가 (예, CPU 가 사용 중인 시간의 퍼센트?) 그러한 이용률을 예측한 이유는 무엇인가? -c 플래그를 지정하여 예측이 맞는지 확인하시오.
A. 100%라고 생각한다. 두 개의 프로세스 모두 입출력 없이 cpu만 사용하기 때문이다.   
R. ``` ./process-run.py -l 5:100,5:100 -c
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