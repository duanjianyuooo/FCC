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
/*
*@parameter: key is the key identify 
*			n is the cnt of semaphore
*/
int init_keyfile(key_t key, int n)
{
	int semid;
	int i;
	semid = init_semaphore( key, n);
	for (i = 0; i < n; i ++){
		set_semvalue(semid, i, 1);
	}
	return semid;
}

int read_cfg(const char *filename)
{
	
}
int init_cfgfile()
{
	

}