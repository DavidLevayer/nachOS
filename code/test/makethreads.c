#include "syscall.h"


int
main ()
{	
	int i;
	void *f = SynchGetInt;
    int res = UserThreadCreate(f,&i);
    /* not reached */
    return res;
}
