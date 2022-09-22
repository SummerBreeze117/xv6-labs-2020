#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if (argc >= 2)
	{
		printf("usage: pingdong\n");
		exit(1);
	}
	
	int fatherw_fd[2], sonw_fd[2];
	pipe(fatherw_fd);
	pipe(sonw_fd);
	
	if (fork() == 0)
	{
		char buf[64];
		int pid;
		
		pid = getpid();
		
		read(fatherw_fd[0], buf, 64);
		printf("%d: received ping\n", pid);
		write(sonw_fd[1], buf, 1);
	
		exit(0);
	}
	else
	{
		char buf[64];
		int pid;
		
		pid = getpid();
		
		write(fatherw_fd[1], buf, 1);
		read(sonw_fd[0], buf, 64);
		printf("%d: received pong\n", pid);
		
		exit(0);
	}
}