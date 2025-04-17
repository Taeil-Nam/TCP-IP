// SPDX-License-Identifier: MIT

#include "arp.h"

void arp_recv(struct packet *pkt)
{
	struct arp_hdr *arp;

	arp = get_arp_hdr(pkt);

	/*
	 *	Todo:
	 *	- Implement ARP cache table.
	 *	- Construct and send ARP reply packet according to RFC 826.
	 *
	 *	[ARP RFC Description] (https://www.rfc-editor.org/rfc/rfc826)
	 *	?Do I have the hardware type in ar$hrd?
	 *	Yes: (almost definitely)
	 *	[optionally check the hardware length ar$hln]
	 *	?Do I speak the protocol in ar$pro?
	 *	Yes:
	 *	[optionally check the protocol length ar$pln]
	 *	Merge_flag := false
	 *	If the pair <protocol type, sender protocol address> is
	 *		already in my translation table, update the sender
	 *		hardware address field of the entry with the new
	 *		information in the packet and set Merge_flag to true.
	 *	?Am I the target protocol address?
	 *	Yes:
	 *	If Merge_flag is false, add the triplet <protocol type,
	 *		sender protocol address, sender hardware address> to
	 *		the translation table.
	 *	?Is the opcode ares_op$REQUEST?  (NOW look at the opcode!!)
	 *	Yes:
	 *		Swap hardware and protocol fields, putting the local
	 *		hardware and protocol addresses in the sender fields.
	 *		Set the ar$op field to ares_op$REPLY
	 *		Send the packet to the (new) target hardware address on
	 *		the same hardware on which the request was received.
	 */
}
