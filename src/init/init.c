#include "init.h"
#include "../include/file_opt.h"


char * init_memory(key_t key, size_t size, int *shmid)
{
	char *pshm;
	
	if ((pshm = attach_shm(key, size, shmid)) == NULL){
		rm_shm(shmid);
		return NULL;
	}
	return pshm;
}

int init_keyfile()
{
	
}

int init_cfgfile()
{


}