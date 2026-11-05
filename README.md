# Network

Small low-level networking experiments: a UDP client and server in Python and C, and a packet sniffer for Linux and Windows.

## What's in here

```text
webSocket/python/server.py            UDP server on 127.0.0.1:9090, replies "Message received"
webSocket/python/receivingPackets.py  UDP listener on 0.0.0.0:9090, prints sender and payload
webSocket/python/client.py            sends "Hello from UDP" to 127.0.0.1:9090
webSocket/C/UDPclient.c               the same client in C with Winsock (Windows)
webSocket/C/packet_sniffer_linux.c    raw AF_PACKET socket in promiscuous mode
webSocket/C/packet_sniffer_WIN32.c    same idea with pcap on the first network device
```

## How to run it

Python (standard library only). Start one of the two listeners, then send from another terminal:

```bash
cd webSocket/python
python3 server.py        # or: python3 receivingPackets.py (both use port 9090, so run one at a time)
python3 client.py
```

The server prints `Received message from ('127.0.0.1', <port>): Hello from UDP`.

C on Windows: `UDPclient.c` uses Winsock and `packet_sniffer_WIN32.c` needs the pcap headers (Npcap SDK).

The Linux sniffer needs root because raw sockets do. Pass the interface to listen on:

```bash
cd webSocket/C
gcc -Wall -o sniffer packet_sniffer_linux.c
sudo ./sniffer eth0
```

## How it works

UDP has no connection, so the server just `bind`s and loops on `recvfrom`, and every datagram comes with the sender's address. The client doesn't connect either. It calls `sendto` with the destination each time.

The sniffers go one level lower. On Linux, `socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))` gets every Ethernet frame on the machine, and `PACKET_MR_PROMISC` asks the NIC for frames that aren't addressed to it. The Windows version gets the same thing through `pcap_open_live`. Both only print a line per packet for now and don't parse headers.

## Limitations

- No packet parsing yet. The sniffers count packets but don't read Ethernet/IP/UDP headers.
- `client.py` doesn't wait for the server's reply.

## License

MIT. See [LICENSE](LICENSE).
