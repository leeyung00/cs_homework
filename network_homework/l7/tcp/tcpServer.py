from socket import *

serverPort = 12000
serverName = 'lee'  
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind((serverName, serverPort))
serverSocket.listen(1)
print('The server is ready to receive')
while True:
    connectionSocket, clientAddress = serverSocket.accept()
    message = connectionSocket.recv(2048)
    modifiedMessage = message.decode().upper()
    connectionSocket.send(modifiedMessage.encode())
    connectionSocket.close()
