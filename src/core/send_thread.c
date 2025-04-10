// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "send_thread.h"
#include "menu.h"

void *send_thread(void *arg)
{
	char user_input[64];
	struct send_thread_info sti;

	memcpy(&sti, arg, sizeof(sti));

	while (true) {
		printf("\n"
		       "====================================\n"
		       "1. Send ARP Request (arping)\n"
		       "2. Send ICMP Echo (ping)\n"
		       "3. Send UDP Datagram\n"
		       "\n"
		       "Enter \"exit\" to exit program\n"
		       "====================================\n"
		       "Select: ");

		if (fgets(user_input, sizeof(user_input), stdin)) {
			if (strncmp(user_input, "exit", 4) == 0)
				exit(EXIT_SUCCESS);

			switch (atoi(user_input)) {
				break;
			case MENU_ARP:
				printf("Sent ARP Request\n");
				break;
			case MENU_ICMP:
				printf("Sent ICMP Echo\n");
				break;
			case MENU_UDP:
				printf("Sent UDP Datagram\n");
				break;
			}
		}
	}
	return (void *)THREAD_SUCCESS;
}
