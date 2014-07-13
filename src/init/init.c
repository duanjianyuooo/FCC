#include "init.h"


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
	int ret;
	
	semid = init_semaphore( key, n);
	for (i = 0; i < n; i ++){
		ret = set_semvalue(semid, i, 1);
		if (ret == -1) {
			return -2;
		}
	}
	return semid;
}

int read_cfg(const char *filename, initcfg *init_cfg)
{
	FILE *fp;
	unsigned char buff[128];
	unsigned char *pbuff;
	int term_no = 0;
	int i = 0;
	
	if (( fp= fopen(filename, "a+"))== NULL){
		run_log("!!!fopen [%s] failed ", filename);
		return -1;
	}
	while(fgets(buff, 128, fp)){
		pbuff = trim_all(buff);

		for (i = 0;*pbuff != '='; pbuff++, i++){
			init_cfg[term_no].name[i] = *pbuff;
		}
		init_cfg[term_no].name[i]= '\0';
		for (i = 0,  ++pbuff; *pbuff != '\0'; pbuff++, i++){
			init_cfg[term_no].value[i] = *pbuff;
		}	
		init_cfg[term_no].value[i]= '\0';
		run_log("name is %s value is %s",init_cfg[term_no].name, init_cfg[term_no].value );
		term_no++;
	}
	bzero((init_cfg+term_no), sizeof(struct INITCFG));
	fclose(fp);
	return term_no;
	
}

int read_cfg_by_name(initcfg *initcfg, const char *name, int *item_no)
{
	while(*item_no){
		if (strcmp(initcfg->name, name) == 0){
			return atoi(initcfg->value);
		}
		initcfg++;
		*item_no--;
	}
	run_log("there is no config item named [%s]", name);
	if (*item_no < MAX_CONFIG) {
		memcpy ((initcfg + *item_no)->name, name, strlen(name));
		(initcfg + *item_no)->value[0] = '0'; 
		*item_no ++;
	}
	return -1;
}

int init_cfgfile(PROCESS_COM *common)
{
	if (!if_file_exist(CFGFILE)){
		run_log("there is no file named [%s]", CFGFILE);
		return -1;
	}
	
	initcfg configure[MAX_CONFIG];
	int *item_no;
	PLINK *gun_list;
	int ret;
	int i;
	
	*item_no = read_cfg(CFGFILE, configure);
	common->if_open_dlb = read_cfg_by_name(configure, "IF_OPEN_DLB", item_no);
	if ((ret = init_gun_cfg(common)) == -1) {
		run_log("!!! init_gun_cfg failed ");
		return -1;
	}

	for ( i = 0 ; i < MAX_CHANNEL_NO; i++) {
		//((PGUN)(common->gun_list))->data->back_channel
	}
	common->gun_no = ret;
	return 0;
}

int init_gun_cfg (PROCESS_COM *common)
{
	PGUN gun;
	PLINK gun_list;
	unsigned char buffer[sizeof(GUN) *64];
	int ret;
	int gunno = 0;

	if ((ret = my_fread(GUNCFG, buffer, sizeof(GUN), 1)) == -1) {		
		run_log("my_read failed");
		return -1;
	}

	make_list(gun_list);
	
	while ( gunno < ret ){
		gun = malloc (sizeof(GUN));
		bzero( gun, sizeof(GUN));
		memcpy( gun, buffer+ gunno*sizeof(GUN), sizeof(GUN));
		add_list(gun_list, (void *)gun);
		gunno++;
	}
	common->gun_list = gun_list;
	return gunno;
}

int init_oil_cfg ()
{

}

int init_tank_cfg()
{

}
int listen_channel_process()
{

}