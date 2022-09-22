#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage : xargs command ...\n");
		exit(0);
	}
	
	char *args[MAXARG];
	int numArg = argc - 1;
	for (int i = 1; i < argc; i ++ ) {
		args[i - 1] = argv[i];
	}
	
	char buf[128];
	char *p = buf;
	while ((read(0, p, 1)) > 0 )
	{
		if ( *p == '\n' )
		{
			*p = 0;
			args[numArg] = buf;
			args[numArg + 1] = "\0";
			if( fork() == 0 )  {
				exec(args[0], args);
			}
			else {
				wait(0);
			}
		}
		p ++;
	}
	exit(0);
}