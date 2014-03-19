#include "syscall.h"


int
main ()
{	
	int i = 4;
	void *f = SynchPutInt;
    int res = UserThreadCreate(f,&i);
    /* not reached */
    return res;
}
