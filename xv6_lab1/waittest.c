#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void spin();

int main()
{
	int pid = fork();
	printf(1, "%d\n", pid);
	if (pid == 0) //child
	{
		spin();
	}
	else //parent
	{
		int *status = 0;
		int options = 0;
		printf(1, "waiting \n");
		waitpid(pid, status, options);
		printf(1, "done waiting \n");	
	}
	exit(0);
}

void spin()
{
	int i = 0;
	for (i = 0; i < 50; i ++)
		printf(1, " i = %d", i);
	exit(0);
}
