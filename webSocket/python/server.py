import socket

# Server IP and port
IP = '127.0.0.1'  # localhost
PORT = 9090

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the IP and port
sock.bind((IP, PORT))
print(f"Server listening on {IP}:{PORT}...")

while True:
    # Receive data from a client
    data, addr = sock.recvfrom(1024)  # buffer size 1024 bytes
    print(f"Received message from {addr}: {data.decode('utf-8')}")                                              
    
    # Optionally send a response
    response = "Message received".encode('utf-8')
    sock.sendto(response, addr)