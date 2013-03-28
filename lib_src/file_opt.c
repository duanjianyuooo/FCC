#include "../include/file_opt.h"
#include <sys/shm.h>
#include <sys/ipc.h>

/**
*@filename: the dict file
*@buf:the buf to write must end of '\0'
*@return 0 is OK; errno is -1
*/
int write_to_file(const char *filename, char *buf)
{
	int fd;
	int len;
	int ret;
	int len_left;
	int sum = 0;
	char *pbuf;
	
	if ((fd = open(filename, O_RDWR|O_CREAT|O_APPEND, 00644)) == -1){
		printf("the %d is fail to be open \n", fd);		
		return -1;
	}

	pbuf = buf;
	len = strlen(buf);
	len_left = len;

	do{
		ret = write (fd, pbuf, len_left);		
		if (ret == -1){
			printf("write to [%s] failed a total of writed bytes are [%d], \
				check the filename whether useful\n", filename, sum);
			return -1;
		}
		sum += ret;
		pbuf += ret;
		len_left -= ret;
	}while( len_left > 0 );
	
	close (fd);
	printf("%s", buf);
	return 0;
}


/*
*@param: the same as printf
*@return: 0 is OK , err is -1
*@discribe: it printf something over standard output,and store the message in LOGFILEPIX
*/
int run_log(char *fmt, ...)
{
	int fd;
	int ret;
	time_t t;
	struct tm *tm;
	char message[MSGLEN];
	int message_len;
	int len_left;
	char *pmes;
	va_list vl;

	memset (message, 0, MSGLEN);
	pmes = message;

	//getenv ("MYSPACE");

	time (&t);
	tm = localtime(&t);

	sprintf(pmes, "%02d-%02d-%02d:", tm->tm_hour, tm->tm_min, tm->tm_sec);
	pmes += strlen (message);
	sprintf (pmes, "%s (%d)  ", __FILE__, __LINE__);
	pmes += strlen(pmes);

	va_start (vl, fmt);
	vsprintf (pmes, fmt, vl);
	va_end (vl);

	message[strlen(message)] = '\n';
	pmes = message;
	
	ret = write_to_file(LOGFILEPIX, pmes);
	if (ret == -1){
		printf("there is something wrong with the run_log function ,but it will not case any invocatable thing\n");
		return -1;
	}
	
	return 0;
}

/*
*@prief : a series of functions aim to operate share memory
*attach_shm : get and attach a share memory 
*
*/
char * attach_shm(key_t key, size_t size, int  *shmid)
{
	char *pshm;
	
	*shmid = shmget(key, size, IPC_CREAT|00666);
	if (*shmid == -1){
		run_log("!!!shmget failed , %s", strerror(errno));
		return NULL;
	}

	pshm = shmat(*shmid, NULL, 0);
	if (pshm == NULL){
		run_log("!!!shmat failed , %s", strerror(errno));
		if (shmctl(*shmid, IPC_RMID, NULL ) == -1){
			run_log("!!!shmrm failed , %s", strerror(errno));
		}
		return NULL;
	}

	return pshm;
}

int detach_shm(char *address, int shmid)
{
	struct shmid_ds buf;
	int i = 0;
	int ret;

	if ( shmctl(shmid, IPC_STAT, &buf) != shmid){
		run_log("!!!shmctl failed %s", strerror(errno));
		return -1;
	}
	for ( i = 0; i < buf.shm_nattch; i ++){
		if (buf.shm_cpid == getpid())
			break;
	}
	if (i == buf.shm_nattch){
		run_log("!!!there is no pid which is current process attaching at share memory");
		return -2;
	}
	ret = shmdt(address);
	if (ret == -1){
		run_log("!!!shmdt faied %s", strerror(errno));
		return -1;
	}

	return 0;
}

int rm_shm(int shmid)
{
	if (shmctl(shmid, IPC_RMID, NULL) == -1){
		run_log("!!!shmctl faied %s", strerror(errno));
		return -1;
	}

	return 0;
}

int init_semaphore(key_t key, int n)
{
	int ret;
	ret = semget(key, n, IPC_CREAT|0666);
	if (ret == -1){
		run_log("!!!semget failed %s", strerror(errno));
		return -1;
	}
}
