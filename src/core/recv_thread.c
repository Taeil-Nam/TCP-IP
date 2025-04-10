// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/epoll.h>

#include "recv_thread.h"

#define MAX_EVENTS 100

void *recv_thread(void *arg)
{
	struct recv_thread_info rti;

	memcpy(&rti, arg, sizeof(rti));

	/* Handle incoming packets */
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
			if (events[i].data.fd == rti.raw_sock)
				(void)0; // dummy code
				// printf("Packet received.\n");
		}
	}
	return (void *)THREAD_SUCCESS;
}
