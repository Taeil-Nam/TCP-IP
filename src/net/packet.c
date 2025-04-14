// SPDX-License-Identifier: MIT

#include "packet.h"
#include "ethernet.h"

void handle_recv_packet(struct packet *pkt)
{
	eth_recv(pkt);
}
