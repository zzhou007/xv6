#include "types.h"
#include "user.h"
#include "syscall.h"
#include "stat.h"

int
main()
{
	int i = count();
	printf(1, "count = %d", i);
	
	exit(0);
}
