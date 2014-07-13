#ifndef __TCP_LIB__
#define __TCP_LIB__
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int tcp_connect(const char * ip, const int port);
int tcp_disconnect(int socket);
int tcp_send(int socket, const unsigned char  *buffer, const size_t size);
int tcp_receive();

#endif 
