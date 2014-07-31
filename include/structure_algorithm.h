#ifndef __STR_ALG__
#define __STR_ALG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	void * data;
	struct node * next;
}LINK, *PLINK;

PLINK make_list(PLINK  list);
int add_list(PLINK list, void *new_node );
int del_dup_element(char * src, size_t src_len, char * dest) ;
int del_dup_element2(char * src, size_t src_len, char * dest) ;


#endif
