#ifndef __TCP_LIB__
#define __TCP_LIB__

int tcp_connect(char *ip, int port);
int tcp_disconnect();
int tcp_send();
int tcp_receive();

#endif 
