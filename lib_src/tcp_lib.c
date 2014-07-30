#include "tcp_lib.h"
#include "file_opt.h"
/**
*@parm: 
*@return: if success return socket for use ,if not return negative 
*@describe:
*/
int tcp_connect(const char * ip, const int port)
{
	int sock, ret;
	struct sockaddr_in sev_addr;
	struct pollfd pfd;
	
	sev_addr.sin_addr.s_addr = inet_addr(ip);
	if ((sock = socket( AF_INET, SOCK_STREAM, 0)) == -1){
		run_log("!!!socket failed [%s]", strerror(errno));
		return -1;
	}

	pfd.fd = sock;
	pfd.events = POLLOUT;
	if (( ret = connect ( sock, (struct sockaddr *)&sev_addr, sizeof(sev_addr))) == -1) {
		if ( errno == EINTR ) {
			while ( poll ( &pfd, 1, -1 ) == -1){
				if (errno == EINTR) {
					continue;
				}
				else {
					run_log("!!!poll wrong [%s]", strerror(errno));
					return -2;
				}
			}
		}
		else {
			run_log("!!!connect failed [%s]", strerror(errno));
			return -3;
		}
	}
	run_log("connect to [%s] success", ip);
	return sock;
}

int tcp_server_init()
{
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	listen(sock, 5);

	while (1) {

		//select(sock+1, 
	}
}
/*
*according to APUE , close socket can only deallocate it ,but when socket is dupped 
*close will take effact after all sockets is closed ,whill shutdown call can make it immediately
*in my opinion, sometimes a used socket closed can't be used immediately may be 
* associate with this. of course , it sould make some tests to verfy the assumption
*/

/*
* how : SHUT_RD close read right now only
*	     SHUT_WR close write right now only
*          SHUT_RDWR close both read and write right now
*/
int close_sock_now(int sock, int how)
{
	int ret;
	ret = shutdown(sock, how);
	if (ret == -1) {
		run_log("!!!shutdown socket [%d] failed", sock);
		return -1;
	}
	return 0;
}
int tcp_send(int socket, const unsigned char  *buffer, const size_t size)
{
	
}

int tcp_receive(int socket, unsigned char *buffer, size_t size)
{

}
int udp_send()
{

}

int udp_receive()
{

}

