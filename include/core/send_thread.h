/* SPDX-License-Identifier: MIT */

#ifndef SEND_THREAD_H
#define SEND_THREAD_H

#include <pthread.h>

#include "thread.h"

struct send_thread_info {
	pthread_t thread_id;
	enum thread_type type;
	int raw_sock;
};

void *send_thread(void *arg);

#endif
