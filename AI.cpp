#include "AI.h"
#include <cstring>
#include "libpcap-1.5.3/pcap/pcap.h"
#include "util.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

static int packetCount = 0;
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr,
		const u_char* packet) {
	std::cout << ++packetCount << " packet(s) captured" << std::endl;
}

void AI::doTurn(World *world) {
	char *dev;
	pcap_t *descr;
	char errbuf[PCAP_ERRBUF_SIZE];

//	dev = pcap_lookupdev(errbuf);
//	if (dev == NULL) {
//		std::cout << "pcap_lookupdev() failed: " << errbuf << std::endl;
//		return;
//	}

	dev=strdup("lo");
	std::cerr << dev << std::endl;
	descr = pcap_open_live(dev, BUFSIZ, 0, -1, errbuf);
	if (descr == NULL) {
		std::cout << "pcap_open_live() failed: " << errbuf << std::endl;
		return;
	}

	if (pcap_loop(descr, 10, packetHandler, NULL) < 0) {
		std::cout << "pcap_loop() failed: " << pcap_geterr(descr);
		return;
	}

	std::cout << "capture finished" << std::endl;
}
