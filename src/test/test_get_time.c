#include "unp.h"
#include "file_opt.h"
//#include "apue.h"

int main(int argc, char *argv[])
{
	int sockfd, n;
	struct sockaddr_in servaddr;
	unsigned char readbuf[MAXLINE + 1];

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet pton %s failed", argv[1]);

	Connect(sockfd, (SA*)&servaddr, sizeof(SA));

	while ( (n = read(sockfd, readbuf, MAXLINE)) > 0) {
		readbuf[n] = 0;
		if (fputs(readbuf, stdout) < 0)
			err_sys("fputs error");
	}

	if (n < 0)
		err_sys("read error");

	exit(0);
}
