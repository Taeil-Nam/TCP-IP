/* SPDX-License-Identifier: MIT */

#ifndef ARP_H
#define ARP_H

#include <linux/types.h>

#include "packet.h"
#include "ethernet.h"

/* ARP protocol HARDWARE identifiers. */
#define ARPHRD_NETROM	0		/* from KA9Q: NET/ROM pseudo	*/
#define ARPHRD_ETHER	1		/* Ethernet 10Mbps		*/
#define	ARPHRD_EETHER	2		/* Experimental Ethernet	*/
#define	ARPHRD_AX25	3		/* AX.25 Level 2		*/
#define	ARPHRD_PRONET	4		/* PROnet token ring		*/
#define	ARPHRD_CHAOS	5		/* Chaosnet			*/
#define	ARPHRD_IEEE802	6		/* IEEE 802.2 Ethernet/TR/TB	*/
#define	ARPHRD_ARCNET	7		/* ARCnet			*/
#define	ARPHRD_APPLETLK	8		/* APPLEtalk			*/
#define ARPHRD_DLCI	15		/* Frame Relay DLCI		*/
#define ARPHRD_ATM	19		/* ATM				*/
#define ARPHRD_METRICOM	23		/* Metricom STRIP (new IANA id)	*/
#define	ARPHRD_IEEE1394	24		/* IEEE 1394 IPv4 - RFC 2734	*/
#define ARPHRD_EUI64	27		/* EUI-64			*/
#define ARPHRD_INFINIBAND 32		/* InfiniBand			*/

struct arp_hdr {
	__be16		ar_hrd;
	__be16		ar_pro;
	unsigned char	ar_hln;
	unsigned char	ar_pln;
	__be16		ar_op;

	unsigned char	ar_sha[MAC_LEN];
	unsigned char	ar_spa[4];
	unsigned char	ar_tha[MAC_LEN];
	unsigned char	ar_tpa[4];
} __attribute__((packed));

void arp_recv(struct packet *pkt);

static inline struct arp_hdr *get_arp_hdr(struct packet *pkt)
{
	return (struct arp_hdr *)pkt_get_network_header(pkt);
}

#endif
