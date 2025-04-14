/* SPDX-License-Identifier: MIT */

#ifndef ETHERNET_H
#define ETHERNET_H

#include <linux/types.h>

#include "packet.h"

#define MAC_LEN 6

struct eth_hdr {
	unsigned char	dst_mac[MAC_LEN];
	unsigned char	src_max[MAC_LEN];
	__be16		type;
} __attribute__((packed));

void eth_recv(struct packet *pkt);

static inline struct eth_hdr *get_eth_hdr(struct packet *pkt)
{
	return (struct eth_hdr *)pkt_get_mac_header(pkt);
}

#endif
