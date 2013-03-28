#ifndef __IFSF_COMMON__
#define __IFSF_COMMON__

#define MAX_CACULA 1
#define MAX_DISPOINT 16


typedef struct {
	unsigned char Nb_Products;//number of products
	unsigned char Nb_Fuelling_Modes; //number of fuelling modes
	unsigned char Nb_Meters;
	unsigned char Nb_Fp; //
}C_DAT;

/**
*the dispensors database for preserving dispensor messages and transactions
*/
typedef struct {
	C_DAT c_dat[MAX_CACULA];
	
}IFSF_SHM;

IFSF_SHM *ifsf_shm = NULL;

#endif
