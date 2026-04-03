import socket 

IP =  '127.0.0.1'.encode("utf-8")
PORT = 9090
Date= "Hello from UDP".encode("utf-8")

sock.sendto(Date, (IP , PORT))

