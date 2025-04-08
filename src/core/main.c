#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static int raw_sock = -1;

static void init();
static void run();

int main()
{
	init();
	run();
	return 0;
}

static void init()
{
	/* Create raw socket */
	raw_sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (raw_sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* Set socket as non-blocking */
	int flag = fcntl(raw_sock, F_GETFL, 0);
	if (flag == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
	if (fcntl(raw_sock, F_SETFL, flag | O_NONBLOCK) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	/* Create epoll */
	/* Add stdin recv event into epoll*/
	/* Add raw socket recv event into epoll */

}

static void run()
{

}