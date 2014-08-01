#include "../include/terminal.h"

int termopen(const char *ttyname, int bps, int databits, char parity, int stopbits)
{
	int fd;
	struct termios termios_new;
	struct serial_struct ss, ss_set;
	
	fd = open(ttyname, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0) {
		printf("打开串口[%s]失败", ttyname);
		return -1;
	}
	
	
	tcgetattr(fd, &termios_new);

	/* BPS */
	switch (bps) {
	case 1200:
		cfsetispeed(&termios_new, B1200); cfsetospeed(&termios_new, B1200); break;
	case 2400:
		cfsetispeed(&termios_new, B2400); cfsetospeed(&termios_new, B2400); break;
	case 4800:
		cfsetispeed(&termios_new, B4800); cfsetospeed(&termios_new, B4800); break;
	case 9600:
		cfsetispeed(&termios_new, B9600); cfsetospeed(&termios_new, B9600); break;
	case 19200:
		cfsetispeed(&termios_new, B19200); cfsetospeed(&termios_new, B19200); break;
	case 38400:
		cfsetispeed(&termios_new, B38400); cfsetospeed(&termios_new, B38400); break;
	case 57600:
		cfsetispeed(&termios_new, B57600); cfsetospeed(&termios_new, B57600); break;
	case 115200:
		cfsetispeed(&termios_new, B115200); cfsetospeed(&termios_new, B115200); break;
	case 230400:
		cfsetispeed(&termios_new, B230400); cfsetospeed(&termios_new, B230400); break;
	case 5760:
		cfsetispeed(&termios_new, B38400); cfsetospeed(&termios_new, B38400); 
		tcflush(fd,TCIFLUSH);/*handle unrecevie char*/  
    		tcsetattr(fd,TCSANOW,&termios_new);  
    		if((ioctl(fd,TIOCGSERIAL,&ss))<0){  
        		printf("BAUD: error to get the serial_struct info:%s\n",strerror(errno));  
        		return -1;  
    		}  
    		ss.flags = ASYNC_SPD_CUST;  
    		ss.custom_divisor = ss.baud_base / bps;  
    		if((ioctl(fd,TIOCSSERIAL,&ss))<0){  
        		printf("BAUD: error to set serial_struct:%s\n",strerror(errno));  
        		return -2;  
    		}  
    		ioctl(fd,TIOCGSERIAL,&ss_set);  
    		printf("BAUD: success set baud to %d,custom_divisor=%d,baud_base=%d\n",  
            		bps, ss_set.custom_divisor,ss_set.baud_base);  
		
   		break;
	default:
		printf("打开%s失败, 参数错误, bps: %d", ttyname, bps);
		return -1;

	}

	/* Data bits */
	termios_new.c_cflag &= ~CSIZE;
	switch (databits) {
	case 5:
		termios_new.c_cflag |= CS5;
		break;
	case 6:
		termios_new.c_cflag |= CS6;
		break;
	case 7:
		termios_new.c_cflag |= CS7;
		break;
	case 8:
		termios_new.c_cflag |= CS8;
		break;
	default:
		printf("打开%s失败, 参数错误, databits: %d", ttyname, databits);
		return -1;
	}

	/* parity checking */
	termios_new.c_iflag |= INPCK;
	switch (parity) {
	case 'N': case 'n':
		termios_new.c_cflag &= ~PARENB;   /* Clear parity enable */
		termios_new.c_iflag &= ~INPCK;
		break;
	case 'O': case 'o':
		termios_new.c_cflag |= PARENB;
		termios_new.c_cflag |= PARODD;
		break;
	case 'E': case 'e':
		termios_new.c_cflag |= PARENB;
		termios_new.c_cflag &= ~PARODD;
		break;
	case 'S': case 's':
		termios_new.c_cflag &= ~PARENB;
		break;
	default:
		printf("打开%s失败, 参数错误, parity: %c", ttyname, parity);
		return -1;
	}

	/* stop bit */
	switch (stopbits) {
	case 1:
		termios_new.c_cflag &= ~CSTOPB;
		break;
	case 2:
		termios_new.c_cflag |= CSTOPB;
		break;
	default:
		printf("打开%s失败, 参数错误, stopbits: %d", ttyname, stopbits);
		return -1;
	}

	/* no start bit */
	termios_new.c_cflag |= CLOCAL;
	termios_new.c_cflag |= CREAD;          // Make port can read
	termios_new.c_cflag &= ~CRTSCTS;       // NO flow control
	termios_new.c_oflag = 0;
	termios_new.c_lflag = 0;
	termios_new.c_iflag &= ~(IXON |IXOFF |IXANY);
	termios_new.c_iflag &= ~(ISTRIP | ICRNL);
	termios_new.c_cc[VTIME] = 1;           // unit: 1/10 second.
	termios_new.c_cc[VMIN] = 1;            // minimal characters for reading 

	tcflush(fd, TCIOFLUSH);

	/* 0 on success, -1 on failure */
	if (tcsetattr(fd, TCSANOW, &termios_new) == 0) {
		return fd;
	}

	close(fd);
	return -1;
}

int termread (int fd, char *buf, int n)
{
	
}
int termwrite (int fd, char *buf, int n)
{

}


