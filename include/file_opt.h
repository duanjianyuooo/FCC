#ifndef __FILE_OPT__
#define __FILE_OPT__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>

#define MSGLEN 4096
#define NAMELEN 128
#define LOGFILEPIX "./run_log.bak"

union semphore_buf{
	char buf;
	
};

int run_log(char *  fmt, ...); 
int write_to_file(const char * filename, char * buf);
char * attach_shm(key_t key, size_t size, int  *shmid);
int detach_shm(char *address, int shmid);
int rm_shm(int shmid);

#endif