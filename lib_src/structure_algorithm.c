#include "structure_algorithm.h"

PLINK make_list(PLINK  list)
{
	list = malloc (sizeof(LINK));
	list->data = NULL;
	list->next = NULL;
	return list;
}

void delet_list(PLINK list)
{
	PLINK p;
	PLINK pf;
	p = list;
	while (NULL != p->next) {
		if (NULL != p->data) {
			free(p->data);
			p->data = NULL;
		}
		pf = p;
		p = p->next;
		free(pf);
		pf = NULL;
	}
}
int add_list(PLINK list, void *new_node)
{
	PLINK p;
	PLINK new_p;
	int node_no = 0;
	
	p = list;
	while (NULL != p->next) {
		p = p->next;
		node_no++;
	}

	new_p = (PLINK)malloc(sizeof(LINK));
	new_p->data = new_node;
	new_p->next = NULL;
	p->next = new_p;
		
	return node_no;
}

int del_dup_element(char * src, size_t src_len, char * dest) 
{
	int sum = 0;
	int i;
	int j;
	for ( i = 0; i < src_len; i++) {
		for ( j = 0; j < sum; j++) {
			if ( src[i] == dest[j] ) {
				break;
			}
			if ( j == sum ) {
				dest[j] = src[i];
				sum += 1;
			}
		}
	}
	return sum;
}
/*
** 	this algorithm use hash value so that the time complexity reduce to O(n)
**	this  function is used to delet  repeated elements of src array and 
**	make a new array to store the result unique elements
*/
int del_dup_element2(char * src, size_t src_len, char * dest) 
{
	char tmp[src_len];
	int i;
	int j;

	bzero ( tmp, src_len);
	for ( i = 0; i < src_len; i++) {
		if ( tmp[src[i]] == 0) {
			tmp[src[i]] == 1;
		}
	}

	for ( i = 0 , j = 0; i < src_len; i++) {
		if ( tmp [i] == 1) {
			dest[j++] = i;
		}
	}
	return j;
}

