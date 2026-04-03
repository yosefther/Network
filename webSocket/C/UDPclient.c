#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    struct sockaddr_in dest_info;
    char *data = "Hello Server.\n";

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset((char *)&dest_info, 0, sizeof(dest_info));
    dest_info.sin_family = AF_INET;
    dest_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    dest_info.sin_port = htons(9090);

    sendto(sock, data, strlen(data), 0,
           (struct sockaddr *)&dest_info, sizeof(dest_info));

    closesocket(sock);
    WSACleanup();
    return 0;
}