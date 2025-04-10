/* SPDX-License-Identifier: MIT */

#ifndef THREAD_H
#define THREAD_H

#define THREAD_SUCCESS 0
#define THREAD_FAILURE 1

enum thread_type {
	RECV_THREAD,
	SEND_THREAD,
	THREAD_TYPE_MAX,
};

#endif
