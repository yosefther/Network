#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PACKET_LEN 512

int main(int argc, char *argv[]) {
    char buffer[PACKET_LEN];
    struct sockaddr_ll saddr;
    socklen_t saddr_len;
    struct packet_mreq mr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <interface>   (for example: sudo %s eth0)\n", argv[0], argv[0]);
        return 1;
    }

    // Create the raw socket (needs root or CAP_NET_RAW)
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    // Turn on promiscuous mode for the chosen interface
    memset(&mr, 0, sizeof(mr));
    mr.mr_ifindex = if_nametoindex(argv[1]);
    if (mr.mr_ifindex == 0) {
        perror("if_nametoindex");
        close(sock);
        return 1;
    }
    mr.mr_type = PACKET_MR_PROMISC;
    if (setsockopt(sock, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr)) < 0) {
        perror("setsockopt");
        close(sock);
        return 1;
    }

    // Getting captured packets
    while (1) {
        saddr_len = sizeof(saddr);
        ssize_t data_size = recvfrom(sock, buffer, PACKET_LEN, 0,
                                     (struct sockaddr *)&saddr, &saddr_len);
        if (data_size < 0) {
            perror("recvfrom");
            break;
        }
        printf("Got one packet (%zd bytes)\n", data_size);
    }

    close(sock);
    return 0;
}
