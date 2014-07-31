#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include "apue.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int termopen (const char *ttyname, int bps, int databits, char parity, int stopbits);
int termread (int fd, char *buf, int n);
int termwrite (int fd, char *buf, int n);
