#include "lis_common.h"

int (*get_status[MAX_TYPE])(int , int , unsigned char) = {
	get_status_heng,
	get_status_jia
};

int (*open_pump[MAX_TYPE])(unsigned char) = {
	open_heng,
	open_jia
};

int lischn(int node)
{
	int i;
	unsigned char status;
	PLINK pump = common->pump_list;
	PPUMP npump;
	unsigned char node_type;
	unsigned char posnum;

	while ((pump = pump->next) != NULL) {
		npump = (PPUMP)pump->data;
		if (npump->node == node) {
			node_type = npump->type;
			posnum = npump->fp_cnt;
			break;
		}
	}

	if ((*open_pump[node_type])(npump->channel) == -1)
		exit(1);
	
	while(1) {
		for (i = 0; i < posnum; i++) {
			(*get_status[node_type])(node , i, status);
			if (1) {

			}
			switch (status) {
				case INVOLIDE:
					break;
				case CLOSE:
					break;
				case IDEL:
					break;
				case START:
					break;
			}
		}
	}
}



