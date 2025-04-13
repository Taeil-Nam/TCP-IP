/* SPDX-License-Identifier: MIT */

#ifndef PACKET_H
#define PACKET_H

#define PKT_SIZE 2048

#include <sys/types.h>

struct packet {
	unsigned char data[PKT_SIZE];
	int len;
	int recv_ifindex;
};

void handle_packet(struct packet *pkt);

#endif
