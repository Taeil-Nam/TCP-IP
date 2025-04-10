/* SPDX-License-Identifier: MIT */

#ifndef RECV_THREAD_H
#define RECV_THREAD_H

#include <pthread.h>

#include "thread.h"

struct recv_thread_info {
	pthread_t thread_id;
	enum thread_type type;
	int raw_sock;
	int epoll_fd;
};

void *recv_thread(void *arg);

#endif
