#include "syscall.h"

int
main ()
{
	int i = 0;
	while(i<4){
   	 PutChar ('c');
   	 i++;
	}

    /* not reached */
    return 0;
}