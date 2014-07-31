#include <apue.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		err_dump("argc is not 3");
	}

	int file[2];	
	int pid, ret;
	char c;
	
	if (pipe(file) == -1) {
		err_dump("pipe error:");
	}
	if ((pid = fork()) == 0){
		close(file[0]);
		while (c != 'd') {
			scanf("%c", &c);
			write(file[1], &c, 1);
		}
		
		exit(0);
	}

	close(file[1]);
	while (c != 'd') {
		read(file[0], &c, 1);
		printf("read from pipe is %c\n", c);
	}
	//waitpid(pid, NULL, NULL, status);
	return 0;
	
}
