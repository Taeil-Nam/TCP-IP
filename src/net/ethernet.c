// SPDX-License-Identifier: MIT

#include <linux/if_ether.h>
#include <arpa/inet.h>

#include "ethernet.h"
#include "arp.h"

void eth_recv(struct packet *pkt)
{
	struct eth_hdr *eth;

	pkt_set_mac_header(pkt, 0);
	eth = get_eth_hdr(pkt);
	pkt_set_network_header(pkt, sizeof(eth));

	switch (ntohs(eth->type)) {
	case ETH_P_ARP:
		arp_recv(pkt);
		break;
	case ETH_P_IP:
		/* Todo: Call ip_handler */
		break;
	default:
		break;
	}
}
