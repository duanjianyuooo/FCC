#ifndef __IFSF_MAIN_H__
#define __IFSF_MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "lis_common.h"

#define VERSION "1.0" 



PROCESS_COM *common = NULL;
IFSF_SHM *ifsf_shm = NULL;

/*the usag of FCC */
static char *usage[][2] = {
	{ "--version", "the version of FCC"},
	{ "--help"   , "the assistant document"},
	{ "-cd"   , "used as a cd"},
	{ "-fcc"   , "used as a forecourt device"},
	{ "end", ""}
};

static int show_usage();
#endif
