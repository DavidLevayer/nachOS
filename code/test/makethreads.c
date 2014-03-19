#include "syscall.h"


int
main ()
{	
	int i = 'c';
	void *f = PutChar;
    int res = UserThreadCreate(f,&i);
    /* not reached */
    return res;
}
