#include "ifsf_main.h"
//#include "../init/init.h"
#include "../ifsf/ifsf_common.h"

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

int main(int argc, char **argv)
{
	int shm_ifsf_id;
	int ret;
	
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
	
	ifsf_shm = (IFSF_SHM *)init_memory((key_t)123, sizeof(IFSF_SHM), &shm_ifsf_id);
	if (ifsf_shm == NULL) {
		run_log("!!!init_memory failed ");
		exit(EXIT_FAILURE);
	}
	
	//init_keyfile();
	//init_cfgfile();
	//start_proc();

	ret = detach_shm(ifsf_shm, shm_ifsf_id);
	if (ret == -2)
		exit(EXIT_FAILURE);
	rm_shm(shm_ifsf_id);
	return 0;
}
