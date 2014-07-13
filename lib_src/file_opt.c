#include "file_opt.h"
#include "apue.h"


int rio_writen(int fd, char *buf, int n)
{
	
}
void set_line( char *file, int line, char *function)
{
	bzero(filename, sizeof(filename));
	memcpy(filename, file, strlen(file));
	lineno = line;
	bzero(funcname, sizeof(funcname));
	memcpy(funcname, function, strlen(function));
}

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
	return 0;
}


/*
*@param: the same as printf
*@return: 0 is OK , err is -1
*@discribe: it printf something over standard output,and store the message in LOGFILEPIX
*/
int __run_log(const char *fmt, ...)
{
	int fd;
	int ret;
	time_t t;
	struct timeb tp;
	struct tm *tm;
	char message[MSGLEN];
	int message_len;
	int len_left;
	char *pmes;
	va_list vl;

	memset (message, 0, MSGLEN);
	pmes = message;

	ftime (&tp);
	tm = localtime(&(tp.time));

	sprintf(pmes, "%04d-%02d-%02d %02d:%02d:%02d.%03d  ", tm->tm_year+1900, \
		tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tp.millitm);
	pmes += strlen (message);
	sprintf (pmes, "%s:%s (%d)  ", filename, funcname, lineno);
	pmes += strlen(pmes);
	sprintf (pmes, "[%d] ", getpid());
	pmes += strlen(pmes);

	va_start (vl, fmt);
	vsprintf (pmes, fmt, vl);
	va_end (vl);

	message[strlen(message)] = '\n';
	pmes = message;
	
	printf("%s", pmes);
#ifdef WRT_LOG_FILE
	ret = write_to_file(LOGFILEPIX, pmes);

	if (ret == -1){
		printf("there is something wrong with the run_log function ,\
			but it will not case any invocatable thing\n");
		return -1;
	}
#endif
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

	if ( shmctl(shmid, IPC_STAT, &buf) == -1){
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

int rm_shm(int *shmid)
{
	if (shmctl(*shmid, IPC_RMID, NULL) == -1){
		run_log("!!!shmctl faied %s", strerror(errno));
		return -1;
	}

	return 0;
}


int init_semaphore(key_t key, int n)
{
	int semid;
	semid = semget(key, n, IPC_CREAT|0666);
	if (semid == -1){
		run_log("!!!semget failed %s", strerror(errno));
		return -1;
	}
	return semid;
}


union semnu{
	int value;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int set_semvalue(int semid, int n, int value)
{
	union semnu semnu;
	semnu.value = value;
	if (semctl(semid, n, SETVAL, semnu) == -1){
		run_log("!!!set_semvalue failed %s", strerror(errno));
		return -1;
	}
	return 0;
}


int sem_p(int semid, unsigned short  n)
{
	struct sembuf buf;
	buf.sem_num = n;
	buf.sem_op = -1;
	if (semop(semid, &buf, 1) == -1){
		run_log("!!! sem_p failed %s", strerror(errno));
		return -1;
	}
	return 0;
}

int sem_v(int semid, unsigned short n)
{	
	struct sembuf buf;
	buf.sem_num = n;
	buf.sem_op = 1;
	if (semop(semid, &buf, 1) == -1){
		run_log("!!! sem_v failed %s", strerror(errno));
		return -1;
	}
	return 0;

}

int rm_sem(int semid, int n)
{
	int i; 
	for ( i = 0; i < n; i++ ) {
		if (semctl(semid, i, IPC_RMID) == -1) {
			run_log("!!!rm sem faild %s", strerror(errno));
			return -1;
		}
	}	
	return 0;
}

unsigned char *trim_all(unsigned char *buf )
{
	int i, firstchar, endpos, firstpos;

	if(  NULL  ==buf){
		return NULL;
		};

	endpos = firstchar = firstpos = 0;
	for ( i = 0; buf[ i ] != '\0'; i++ )
	{
		if ( buf[i] ==' ' || buf[i] == '\t' || buf[i] == '\n' || buf[i] == '\r') {
			if( firstchar == 0 )
				firstpos++;
		}
		else {
			endpos = i;
			firstchar = 1;
		}
	}

	for ( i = firstpos; i <= endpos; i++ )
		buf[i - firstpos] = buf[i];
	buf[i - firstpos] = 0;
	return buf;
}

int if_file_exist(unsigned char *filename)
{
	assert(filename != NULL);
	int mode;
	access(filename, mode);
	return ( F_OK == mode);
}


int my_fread (const char * filename, unsigned char  *buffer, size_t size, size_t  num)
{
	assert(buffer != NULL);
	
	FILE *fp;
	int ret;
	int n = 0 ;
	
	if ( ( fp = fopen( filename, "r")) == NULL) {
		run_log("!!!fopen %s failed because %s", filename, strerror(errno));
		return -1;
	}
	clearerr(fp);
	while ( (ret = fread ( buffer, size, num, fp ))  &&(! feof (fp)) ) {
		buffer += ret*size;
		n += ret;
	}
	if (ferror(fp)){
		run_log("!!!there is something wrong while fread %s", filename);
		return -1;
	}
	fclose(fp);
	return n;
}

/*
*  eg: 	asc ['0','a','A']
*	 	hex [0x00,0x0a,0x0a]
*		lenasc = 3
*		return 3
*/
int asc_to_hex(const char *asc, char *hex, int lenasc)
{
	assert(hex!= NULL);
	int i;
	for(i = 0; i <lenasc; i++){
		if(asc[i]>= '0' && asc[i]<= '9')
			hex[i] = asc[i]-0x30;
		else if (asc[i] >= 'A' && asc[i] <='F')
			hex[i] = asc[i] -0x37;
		else if (asc[i] >= 'a' && asc[i] <='f')
			hex[i] = asc[i] -0x57;
		else{
			run_log("THIS IS A INVALID CARACTOR");
			return -1;
		}
	}
	return i;
}

int hex_to_asc(const char *hex, char *asc, int lenhex)
{
	assert(asc!=NULL);
	int i;
	for ( i=0; i < lenhex; i++ ){
		if ( hex[i]>=( '0'-0x30) && asc[i]<= ('9'-0x30) )
			asc[i] = hex[i]+0x30;
		else if (asc[i] >= ('A'-0x37) && asc[i] <=('F'-0x37))
			asc[i] = hex[i]+0x37;
		else if (asc[i] >= ('a'-0x57) && asc[i] <=('f'-0x57))
			asc[i] = hex[i]+0x57;
		else{
			run_log("THIS IS A INVALID CARACTOR");
			return -1;
		}
	}
	return i;
}

int bcd_to_hex(const char *bcd, char *hex, int lenbcd)
{
	assert(hex!=NULL);
	int i, lenhex;
	for(i = 0, lenhex = 0; i < lenbcd; i++, lenhex+=2){
		hex[lenhex] = (bcd[i]&0xf0)<<4;
		hex[lenhex+1] = bcd[i]&0x0f;
	}
	return lenhex;
}

int hex_to_bcd(const char *hex, char *bcd, int lenhex)
{
	assert(bcd!=NULL);
	int i, lenbcd;
	for(i = 0, lenbcd = 0; i < lenhex; i+=2, lenbcd++){
		bcd[lenbcd] = ((hex[i]&0x0f)<<4)|(hex[i+1]&0x0f);
	}
	return lenbcd;
}

int bcd_to_asc (const char *bcd, char *asc, int lenbcd)
{
	assert(asc != NULL);
	int lenhex = lenbcd+lenbcd;
	char hex[lenhex];
	if ( bcd_to_hex( bcd, hex, lenbcd) != lenhex )
		return -1;
	if ( hex_to_asc( hex, asc, lenhex) != lenhex )
		return -1;
	return lenhex;
}
/*
* file record lock is used for the processors who should attach file at the same time;
* But the mechainesm can't be used for processors mutual exclusion??
*/
void file_lock()
{
	
}


static void err_doit(int, int, const char *, va_list); 
/* 
* Nonfatal error related to a system call. 
* Print a message and return. 
*/ 
void 
err_ret(const char *fmt, ...) 
{ 
	va_list ap; 
	va_start(ap, fmt); 
	err_doit(1, errno, fmt, ap); 
	va_end(ap); 
} 
/* 
* Fatal error related to a system call. 
* Print a message and terminate. 
*/ 
void 
err_sys(const char *fmt, ...) 
{ 
	va_list ap; 
	va_start(ap, fmt); 
	err_doit(1, errno, fmt, ap); 
	va_end(ap); 
	exit(1); 
} 
/* 
* Fatal error unrelated to a system call. 
* Error code passed as explict parameter. 
* Print a message and terminate. 
*/ 
void 
err_exit(int error, const char *fmt, ...) 
{ 
	va_list ap; 
	va_start(ap, fmt); 
	err_doit(1, error, fmt, ap); 
	va_end(ap); 
	exit(1); 
} 
/* 
* Fatal error related to a system call. 
* Print a message, dump core, and terminate. 
*/ 
void 
err_dump(const char *fmt, ...) 
{ 
	va_list ap; 
	va_start(ap, fmt); 
	err_doit(1, errno, fmt, ap); 
	va_end(ap); 
	abort(); /* dump core and terminate */ 
	exit(1); /* shouldn't get here */ 
} 
/* 
* Nonfatal error unrelated to a system call. 
* Print a message and return. 
*/ 
void 
err_msg(const char *fmt, ...) 
{ 
	va_list ap; 
	va_start(ap, fmt); 
	err_doit(0, 0, fmt, ap); 
	va_end(ap); 
} 
/* 
* Fatal error unrelated to a system call. 
* Print a message and terminate. 
*/ 
void 
err_quit(const char *fmt, ...) 
{ 
	va_list ap; 
	va_start(ap, fmt); 
	err_doit(0, 0, fmt, ap); 
	va_end(ap); 
	exit(1); 
} 
/* 
* Print a message and return to caller. 
* Caller specifies "errnoflag". 
*/ 
static void 
err_doit(int errnoflag, int error, const char *fmt,va_list ap) 
{ 
	char buf[MAXLINE]; 
	vsnprintf(buf, MAXLINE, fmt, ap); 
	if (errnoflag) 
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s", strerror(error)); 
	strcat(buf, "\n"); 
	fflush(stdout); /* in case stdout and stderr are the same */
	fputs(buf, stderr); 
	fflush(NULL); /* flushes all stdio output streams */ 
}

int asyn_ioread()
{

}
