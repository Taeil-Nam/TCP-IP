// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>

#define MAX_EVENTS 100

static int raw_sock = -1;
static int epoll_fd = -1;

static void init(void);
static void run(void);

int main()
{
	init();
	run();
	return 0;
}

static void init(void)
{
	int flag;
	struct epoll_event ev;

	/* Create raw socket */
	raw_sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if (raw_sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* Set socket as non-blocking */
	flag = fcntl(raw_sock, F_GETFL, 0);

	if (flag == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	if (fcntl(raw_sock, F_SETFL, flag | O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	/* Create epoll */
	epoll_fd = epoll_create1(0);

	if (epoll_fd == -1) {
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}

	/* Add raw socket into epoll */
	ev.events = EPOLLIN;
	ev.data.fd = raw_sock;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, raw_sock, &ev) == -1) {
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}
}

static void run(void)
{
	/* Check received packet and processing it */
	while (true) {
		struct epoll_event events[MAX_EVENTS];
		int ready_cnt = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		int i;

		if (ready_cnt == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < ready_cnt; i++) {
			if (events[i].data.fd == raw_sock)
				printf("Packet received.\n");
		}
	}
}
