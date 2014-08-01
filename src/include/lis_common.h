#ifndef __LIS_COMMON__
#define __LIS_COMMON__

#include <stdio.h>
#include <stdlib.h>
#include "ifsf_common.h"


static const char * tty[MAX_TTY_NAME] = {
	"/dev/ttyS0",
	"/dev/ttyS1",
	"/dev/ttyS2",
	"/dev/ttyS3",
	"/dev/ttyS4",
	"/dev/ttyS5"
};

extern PROCESS_COM *common;
extern IFSF_SHM *ifsf_shm ;

extern int open_heng(unsigned char channel);
extern int open_jia(unsigned char channel);
extern int get_status_heng(int , int , unsigned char);
extern int get_status_jia(int , int , unsigned char);


int lischn(int node);


#define MAX_CMD 128

int (*get_status[MAX_TYPE])(int , int , unsigned char);
int (*open_pump[MAX_TYPE])(unsigned char);


#endif

