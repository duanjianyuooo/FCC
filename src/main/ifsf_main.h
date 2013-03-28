#ifndef __IFSF_MAIN_H__
#define __IFSF_MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define VERSION "1.0" 


/*the usag of FCC */
static char *usage[][2] = {
	{ "--version", "the version of FCC"},
	{ "--help"   , "the assistant document"},
	{ "end", ""}
};

static int show_usage();

#endif
