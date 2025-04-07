#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mode.h"
#include "recv_mode.h"
#include "send_mode.h"

int main()
{
	while (true) {
		char input[10];
		enum tcpip_mode mode;

		printf("===========================\n"
			"Select Mode\n"
			"0. Exit\n"
			"1. Receiver Mode\n"
			"2. Sender Mode\n"
			"===========================\n"
			"Enter: ");

		if (fgets(input, sizeof(input), stdin) == NULL)
			return 1;

		printf("\n");

		mode = atoi(input);
		switch (mode) {
		case TCPIP_MODE_EXIT:
			return 0;
		case TCPIP_MODE_RECV:
			start_recv_mode();
			break;
		case TCPIP_MODE_SEND:
			start_send_mode();
			break;
		default:
			break;
		}
		printf("\n");
	}
	return 0;
}
