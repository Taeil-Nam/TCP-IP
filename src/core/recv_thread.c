// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_packet.h>

#include "recv_thread.h"
#include "packet.h"

#define MAX_EVENTS 100

void *recv_thread(void *arg)
{
	struct recv_thread_info rti;

	memcpy(&rti, arg, sizeof(rti));

	while (true) {
		struct epoll_event events[MAX_EVENTS];
		int ready_cnt;
		int i;

		ready_cnt = epoll_wait(rti.epoll_fd, events, MAX_EVENTS, -1);

		if (ready_cnt == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < ready_cnt; i++) {
			/* Create and handle received packet */
			if (events[i].data.fd == rti.raw_sock) {
				struct packet *pkt;
				struct sockaddr_ll sa;
				socklen_t sa_len = sizeof(sa);

				pkt = malloc(sizeof(struct packet));

				pkt->len = recvfrom(rti.raw_sock, pkt->data,
						    PKT_SIZE, 0,
						    (struct sockaddr *)&sa,
						    &sa_len);

				if (pkt->len == -1)
					perror("recvfrom");

				pkt->recv_ifindex = sa.sll_ifindex;

				handle_packet(pkt);
				free(pkt);
			} else if (events[i].data.fd == rti.terminate_fd) {
				pthread_exit(0);
			}
		}
	}
	pthread_exit(0);
}
