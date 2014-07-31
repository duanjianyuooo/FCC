#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
int main()
{
	unsigned int a = 0x04030201;
	unsigned int b;
	printf("raw byte order [%08x]\n", a);
	b = htonl(a);
	printf("host to net [%08x]\n", b);
	b = ntohl(b);
	printf("net to host [%08x]\n", b);

	struct sockaddr sockad;
	struct sockaddr_in sock_in;
	struct in_addr addr;
	bzero(&addr, sizeof(addr));
	char *ip = "10.1.2.102";

	char ipaddr[INET_ADDRSTRLEN];
	bzero(ipaddr, sizeof(ipaddr));

	inet_pton(AF_INET, (void *)ip, &addr);
	printf("host addr is [%08x]\n", addr);
	inet_ntop(AF_INET, (void *)&addr, ipaddr, INET_ADDRSTRLEN);
	printf("ip addr is %s\n", ipaddr);

	
}

