/* SPDX-License-Identifier: MIT */

#ifndef PACKET_H
#define PACKET_H

#include <linux/types.h>

#define PKT_SIZE 2048

struct packet {
	unsigned char	data[PKT_SIZE];

	int		recv_ifindex; /* Received network interface index */
	int		len;

	/* Offset from data[0] to each layer header */
	__u16		mac_header;
	__u16		network_header;
	__u16		transport_header;
};

void handle_recv_packet(struct packet *pkt);

static inline unsigned char *pkt_get_mac_header(struct packet *pkt)
{
	return pkt->data + pkt->mac_header;
}

static inline unsigned char *pkt_set_mac_header(struct packet *pkt,
						const int offset)
{
	return pkt->data + offset;
}

#endif
