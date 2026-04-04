#include <pcap.h>
#include <stdio.h>

#define PACKET_LEN 512

void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *data) {
    if (header->caplen > 0)
        printf("Got one packet\n");
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *dev;

    // Find available devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Error finding devices: %s\n", errbuf);
        return 1;
    }

    dev = alldevs; // Use first available device
    if (!dev) {
        fprintf(stderr, "No devices found.\n");
        return 1;
    }

    // Open device in promiscuous mode
    pcap_t *handle = pcap_open_live(dev->name, PACKET_LEN, 1, 1000, errbuf);
    if (!handle) {
        fprintf(stderr, "Failed to open device: %s\n", errbuf);
        pcap_freealldevs(alldevs);
        return 1;
    }

    pcap_freealldevs(alldevs);

    // Capture packets in a loop
    pcap_loop(handle, 0, packet_handler, NULL);

    pcap_close(handle);
    return 0;
}