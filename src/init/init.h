#ifndef __INIT_H__
#define __INIT_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define CFGPATH "/home/App/ifsf/etc/"
#define CDATKEY 


struct initcfg{
	unsigned char if_second_config;
	unsigned char 
};
/**
*@param: key is the key for alocating memory address,
* 		  size is the size of share memory
*@return: return the memory address
*@discribe: this function applys for a region of share memory 
*/
char * init_memory(key_t key, size_t size, int *shmid);
int init_keyfile(key_t key, int n);


#endif
