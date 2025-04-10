// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include "thread.h"
#include "recv_thread.h"
#include "send_thread.h"

static int raw_sock = -1;
static int epoll_fd = -1;

static void init(void);
static void run(void);
static void terminate(void);

int main()
{
	init();
	run();
	terminate();
	return 0;
}

static void init(void)
{
	int flag;
	struct epoll_event ev;

	raw_sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if (raw_sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	flag = fcntl(raw_sock, F_GETFL, 0);

	if (flag == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	if (fcntl(raw_sock, F_SETFL, flag | O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	epoll_fd = epoll_create1(0);

	if (epoll_fd == -1) {
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN;
	ev.data.fd = raw_sock;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, raw_sock, &ev) == -1) {
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}
}

static void run(void)
{
	void *thread_ret;

	struct recv_thread_info *rti =
		calloc(1, sizeof(struct recv_thread_info));

	struct send_thread_info *sti =
		calloc(1, sizeof(struct send_thread_info));

	rti->type = RECV_THREAD;
	rti->raw_sock = raw_sock;
	rti->epoll_fd = epoll_fd;

	if (pthread_create(&rti->thread_id, NULL, &recv_thread, rti)) {
		perror("pthread_create(recv)");
		exit(EXIT_FAILURE);
	}

	sti->type = SEND_THREAD;
	sti->raw_sock = raw_sock;

	if (pthread_create(&sti->thread_id, NULL, &send_thread, sti)) {
		perror("pthread_create(send)");
		exit(EXIT_FAILURE);
	}

	if (pthread_join(sti->thread_id, &thread_ret)) {
		perror("pthread_join(send)");
		exit(EXIT_FAILURE);
	}
}

static void terminate(void)
{
	close(raw_sock);
	close(epoll_fd);
}
