import socket

IP = "0.0.0.0"
PORT = 9090

# AF_INET is technically the Address Family identifier that points to the IPv4 protocol suite
#
# SOCK_DGRAM  is a constant used to specify the socket type as a datagram socket. 
# In the context of the Internet address family (AF_INET), it almost always uses the UDP (User Datagram Protocol).
sock = socket.socket(socket.AF_INET , socket.SOCK_DGRAM)
sock.bind((IP,PORT))

while True : 
    data , (ip , port) = sock.recvfrom(1024)
    print("Sender : {} and Port {} ".format(ip,port))
    print("Received message : {}".format(data))
    
