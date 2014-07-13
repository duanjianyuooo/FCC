#include "ifsf_main.h"
#include "ifsf_common.h"
#include "file_opt.h"

OIL all_product_in_fcc[MAX_OIL_NO]; //the index of pr_no start at 0/0-based

static int show_usage()
{
	printf("/*******************************/\n");
	printf("*            FCC               */\n");
	printf("/*******************************/\n\n\n");
	int tmp = 0;
	while (strcmp (usage[tmp][0], "end") != 0)
	{
		printf("%s\t\t%s\n", usage[tmp][0], usage[tmp][1]); 
		tmp++;
	}
	return 0;
}

static int start_proc()
{
	int pid;

	do {
		pid = fork();
		if (pid == 0) {
			run_log("begin listening pumps");
			
			int i;
			PLINK p;
			unsigned char gunno = common->gun_no;
			unsigned char channel_node[gunno];
			unsigned char node_list[gunno];
			
			bzero (channel_node, sizeof (channel_node));
			bzero (node_list, sizeof (node_list));
			p = common->gun_list;
			for ( i = 0; i < gunno; i++ ) {
				if (p->data != NULL && p->next != NULL) {
					channel_node[i] = ((PGUN)(p->data))->back_channel;
					p = p->next;
				}
			}
			
			gunno = del_dup_element(channel_node, strlen(channel_node), node_list);
			for ( i = 0; i < gunno; i++ ) {
				if ( node_list [i] != 0) {
					lischn(node_list[i]);
				}
			}
		}
		else 
			break;
	}while(0);
	
}

int main(int argc, char **argv)
{
	int shm_ifsf_id;
	int shm_com_id;
	int ret;
	int semid = 0;
	OIL all_product_in_fcc[MAX_OIL_NO]; //the index is pr_no begin with 0
	
	if (argc == 2)
	{
		if (strcmp (argv[1], "--version")== 0){
			printf("the FCC version is %s\n", VERSION);
		}else{
			printf("the parameter is invalid\n");
			show_usage();
		}
	}
	run_log("IFSF started VERSION is [%s]", VERSION);

	run_log("Start init_memory.....");
	ifsf_shm = (IFSF_SHM *)init_memory((key_t)SHAMEMORY_KEY, sizeof(IFSF_SHM), &shm_ifsf_id);
	if (ifsf_shm == NULL) {
		run_log("!!!init_memory ifsf_shm failed ");
		exit(EXIT_FAILURE);
	}
	common = (PROCESS_COM *)init_memory((key_t)SHAMEMORY_KEY2, sizeof(PROCESS_COM), &shm_com_id);
	if (common == NULL) {
		run_log("!!!init_memory  common failed ");
		exit(EXIT_FAILURE);
	}
	
	do {
		run_log("Start init keyfile .....");
		semid = init_keyfile((key_t)SEMAPHORE_SET_KEY, IFSF_STRUCTURE_CNT);
		if ( semid < 0 ) {
			run_log("!!! init_keyfiles SEMAPHORE_SET_KEY failed ");
			break;
		}
		run_log("Start init cfgfile .....");
		ret = init_cfgfile(common);
		if ( ret == -1) {
			run_log("!!!init_cfgfile failed ");
			//break;
		}

		
		run_log("Start proccess .....");
		start_proc();
		while(1);
	}while(0);
	
	ret = detach_shm((char *)ifsf_shm, shm_ifsf_id);
	if (ret == -2)
		exit(EXIT_FAILURE);
	rm_shm(&shm_ifsf_id);	
	
	ret = detach_shm((char *)common, shm_com_id);
	if (ret == -2)
		exit(EXIT_FAILURE);
	rm_shm(&shm_com_id);
	ifsf_shm = NULL;
	common = NULL;

	rm_sem(semid, IFSF_STRUCTURE_CNT);
	return 0;
}
