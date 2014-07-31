#ifndef __IFSF_COMMON__
#define __IFSF_COMMON__

#include "structure_algorithm.h"

#define MAX_CACULA 1
#define MAX_DISPOINT 16
#define MAX_FP 8
#define MAX_OIL_NO 16
#define MAX_CONFIG 32
#define MAX_OIL_PER_PUMP 8
#define MAX_GUN_NO 128
#define MAX_CHANNEL_NO 32
#define MAX_TYPE 2
#define MAX_TTY_NAME 6
#define IFSF_STRUCTURE_CNT 6
#define SHAMEMORY_KEY 001
#define SEMAPHORE_SET_KEY 002
#define SHAMEMORY_KEY2 003

typedef struct {
	unsigned char Nb_Products;//number of products
	unsigned char Nb_Fuelling_Modes; //number of fuelling modes
	unsigned char Nb_Meters;
	unsigned char Nb_Fp; //
}C_DAT;

/*
*the dispensors database for preserving dispensor messages and transactions
*/
typedef struct {
	C_DAT c_dat[MAX_CACULA];
	
}IFSF_SHM;

enum PUMP_TYPE {
	HENGSHAN, JIALIJIA
};

enum FP_STATE{
	INVOLIDE, CLOSE, IDEL, START, AUTH, FUELLING 
};



typedef struct {
	//unsigned char pr_no; // the index of all  oil products in FCC begin with 0
	unsigned char pr_num[4]; //the number of product eg. 00000060
	unsigned char pr_name[7];
	unsigned char price[2];
	unsigned char mode;
}OIL;



typedef struct {
	unsigned char nozzle_no; //the num of all guns  associating with FCC
	unsigned char back_channel;
	unsigned char node;
	unsigned char type;
	unsigned char phy_fp;
	unsigned char log_fp;
	unsigned char phy_nozzle;
	unsigned char log_nozzle;
	unsigned char pr_no;
	unsigned char tlg_no; 
	unsigned char if_used;
}GUN, *PGUN;

typedef struct {
	PGUN data;
	PGUN next;
}GUN_LIST, *PGUN_LIST;

typedef struct {
	unsigned char nozzel_no;
	unsigned char node;
	unsigned char fp;
	unsigned char nozzle;
	unsigned char pr_no;
	unsigned char trans_state;
	unsigned char trans_no;
	unsigned char amount;
	unsigned char volume;
	unsigned char admin;
	unsigned char stime;
	unsigned char stotal;
	unsigned char etime;
	unsigned char etotal;
}TRANSACTION, *PTRANSACTION;

typedef struct {
	PTRANSACTION data;
	PTRANSACTION next;
}TRANS_LIST , *PTRANS_LIST;

typedef struct {
	unsigned char channel; //the back panel number
	unsigned char node; // node num associate with FUEL
	unsigned char type; 
	unsigned char gun_cnt;
	unsigned char fp_cnt;
	unsigned char pr_cnt;
	PLINK gun_list;
	OIL pump_oil[MAX_OIL_PER_PUMP];
}PUMP, *PPUMP;

typedef struct {
	unsigned char posid;
	unsigned char oil_mode;
	unsigned char pos_stat;
	PLINK gun_list;
}POS;

typedef struct {
	PPUMP data;
	PPUMP next;
}PUMP_LIST ,* PPUMP_LIST;

typedef struct {
	unsigned char if_open_dlb;
	unsigned char if_open_tlg;
	unsigned char tlg_no;
	unsigned char gun_no;
	unsigned char node_channel_type[MAX_CHANNEL_NO][3];
	PLINK pump_list;
	PLINK gun_list;
}PROCESS_COM;




#endif
