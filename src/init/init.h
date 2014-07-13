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
#include <assert.h>
#include <errno.h>
#include "ifsf_common.h"
#include "file_opt.h"

#define CFGPATH "/home/App/ifsf/etc/"
#define CDATKEY 
#define CFGFILE "/home/App/ifsf/etc/cfg.cfg"
#define GUNCFG "/home/App/ifsf/etc/gun.cfg"
#define OILCFG "/home/App/ifsf/etc/oil.cfg"

extern PROCESS_COM *common;
extern IFSF_SHM *ifsf_shm ;
extern OIL all_product_in_fcc[MAX_OIL_NO];

typedef struct INITCFG{
	unsigned char name[64];
	unsigned char value[64];
}initcfg;
/**
*@param: key is the key for alocating memory address,
* 		  size is the size of share memory
*@return: return the memory address
*@discribe: this function applys for a region of share memory 
*/
char * init_memory(key_t key, size_t size, int *shmid);
int init_keyfile(key_t key, int n);
int read_cfg(const char *filename, initcfg *init_cfg);
int read_cfg_by_name(initcfg *initcfg, const char *name, int *item_no);
int init_cfgfile(PROCESS_COM *common);
int init_gun_cfg(PROCESS_COM *common);


#endif
