from socket import *

# udp로 연결하고자 하는 서버의 이름과 포트번호를 지정한다.
serverName = 'lee'
serverPort = 12000

# 소켓을 생성한다. 메서드 안의 값은 각각 ipv4, udp를 의미한다.
clientSocket = socket(AF_INET, SOCK_DGRAM)

# 사용자의 입력을 받아 소문자를 대문자로 치환하는 간단한 비즈니스 로직이다. 
message = input('Input lowercase sentence: ')
clientSocket.sendto(message.encode(), (serverName, serverPort))
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print(modifiedMessage.decode())

# 소켓을 닫아 자원을 해제한다.
clientSocket.close()