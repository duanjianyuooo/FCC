#include "ifsf_common.h"
#include "lis_common.h"
#include "terminal.h"

static int fd;

int open_heng(unsigned char channel)
{
	fd = termopen(tty[channel], 9600, 8, 'N', 1);
	return fd;
}
int get_status_heng(int node, int pos, unsigned char status)
{
	unsigned char cmd[MAX_CMD];
	
	termwrite(fd, cmd, MAX_CMD);
	termread(fd, cmd, MAX_CMD);
}