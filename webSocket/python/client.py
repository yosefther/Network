import socket 

IP =  '127.0.0.1'.encode("utf-8")
PORT = 9090
Data= "Hello from UDP".encode("utf-8")

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.sendto(Data, (IP , PORT) )