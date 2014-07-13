#ifndef __FILE_OPT__
#define __FILE_OPT__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <sys/timeb.h>
#include <apue.h>

#define MSGLEN 4096
#define NAMELEN 128
#define LOGFILEPIX "./run_log.bak"


unsigned char filename[128];
unsigned char funcname[64];
int lineno;


void set_line(char *filaname, int line, char *function);
int __run_log(const char *  fmt, ...); 

#define run_log set_line(__FILE__, __LINE__,(char *)__FUNCTION__), __run_log
int write_to_file(const char * filename, char * buf);
char * attach_shm(key_t key, size_t size, int  *shmid);
int detach_shm(char *address, int shmid);
int rm_shm(int *shmid);
int init_semaphore(key_t key, int n);
int set_semvalue(int semid, int n, int value);
int sem_p(int semid, unsigned short  n);
int sem_v(int semid, unsigned short n);
unsigned char *trim_all(unsigned char *buf );
int if_file_exist(unsigned char *filename);
int my_fread (const char * filename, unsigned char  *buffer, size_t size, size_t  num);
int rm_sem(int, int);
int asc_to_hex(const char *asc, char *hex, int lenasc);
int bcd_to_hex(const char *bcd, char *hex, int lenbcd);
int hex_to_bcd(const char *hex, char *bcd, int lenhex);
int bcd_to_asc (const char *bcd, char *asc, int lenbcd);


#endif
