#include "kernel/types.h"
#include "user/user.h"

void deal(int fa_fd)
{
	int p = -1;
	if ((read(fa_fd, &p, sizeof(int))) <= 0)
	{
		close(fa_fd);
		exit(0);
	}
	printf("prime %d\n", p);
	
	int cld_fd[2];
	pipe(cld_fd);

	if (fork() == 0)
	{
		close(cld_fd[1]);//子进程管道不需要写端了
		deal(cld_fd[0]);
		exit(0);
	}
	else
	{
		close(cld_fd[0]);//父进程管道不需要读端了
		int n;

		while ( (read(fa_fd, &n, sizeof(int))) > 0)
		{
			if (n % p) write(cld_fd[1], &n, sizeof(int));
		}
		close(fa_fd);
		close(cld_fd[1]);
		
		wait(0);
	}
	
}

int main(int argc, char *argv[])
{
	int fd[2];
	pipe(fd);
	
	if (fork() == 0)
	{
		close(fd[1]); //子进程管道不需要写端了
		deal(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]); //父进程管道不需要读端了
		
		int i = 0;
		for (i = 2; i <= 35; ++ i)
		{
			write(fd[1], &i, sizeof(i));
		}
		close(fd[1]); //发送完毕，关闭父进程管道写端
		
		wait(0);
		exit(0);
	}
}
