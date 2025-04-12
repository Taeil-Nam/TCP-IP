// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include "thread.h"
#include "recv_thread.h"
#include "send_thread.h"

static int raw_sock = -1;
static int epoll_fd = -1;
static int terminate_fd = -1;

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

	/* Create and set raw_socket */
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

	/* Create terminate_fd (event fd) */
	terminate_fd = eventfd(0, 0);

	if (terminate_fd == -1) {
		perror("eventfd");
		exit(EXIT_FAILURE);
	}

	/* Create and set epoll events */
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

	ev.events = EPOLLIN;
	ev.data.fd = terminate_fd;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, terminate_fd, &ev) == -1) {
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}
}

static void run(void)
{
	void *thread_ret;

	struct recv_thread_info rti;
	struct send_thread_info sti;

	/* Create recv_thread */
	rti.type = RECV_THREAD;
	rti.raw_sock = raw_sock;
	rti.epoll_fd = epoll_fd;
	rti.terminate_fd = terminate_fd;

	if (pthread_create(&rti.thread_id, NULL, &recv_thread, &rti)) {
		perror("pthread_create(recv)");
		exit(EXIT_FAILURE);
	}

	if (pthread_detach(rti.thread_id)) {
		perror("pthread_detach(recv)");
		exit(EXIT_FAILURE);
	}

	/* Create send_thread */
	sti.type = SEND_THREAD;
	sti.raw_sock = raw_sock;

	if (pthread_create(&sti.thread_id, NULL, &send_thread, &sti)) {
		perror("pthread_create(send)");
		exit(EXIT_FAILURE);
	}

	/* Wait for send_thread to terminate */
	if (pthread_join(sti.thread_id, &thread_ret)) {
		perror("pthread_join(send)");
		exit(EXIT_FAILURE);
	}
}

static void terminate(void)
{
	/* Terminate recv_thread */
	uint64_t val = 1;

	write(terminate_fd, &val, sizeof(val));

	/* Release resources */
	close(raw_sock);
	close(epoll_fd);
}
