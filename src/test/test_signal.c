#include "apue.h"
#include "file_opt.h"

//Sigfunc *

void sig_alarm(int signo)
{
	run_log("pid is %d", getpid());
}

Sigfunc * 
Signal(int signo, Sigfunc *func) 
{ 
	struct sigaction act, oact; 
	act.sa_handler = func; 
	sigemptyset(&act.sa_mask); 
	act.sa_flags = 0; 
	if (signo == SIGALRM) { 
#ifdef SA_INTERRUPT 
		act.sa_flags |= SA_INTERRUPT; 
#endif 
	} else { 
#ifdef SA_RESTART 
		act.sa_flags |= SA_RESTART; 
#endif 
	} 
	if (sigaction(signo, &act, &oact) < 0) {
		return(SIG_ERR); 
	}
	return(oact.sa_handler); 
} 

int main(int argc, char **argv)
{
	alarm(15);
	int pid;
	int status;

	if ((pid = fork()) < 0) {
		err_dump("fork failed");
	}
	else if (pid == 0) {
		Signal(SIGALRM, sig_alarm);
		pause();
	}

	Signal(SIGALRM, sig_alarm);
	wait(&status);
	return 0;
}



