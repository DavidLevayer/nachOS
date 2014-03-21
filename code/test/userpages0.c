#include "syscall.h"

void afficheString(char* s) {
	int nb = 100;
	int i;
	for(i=0;i<nb;i++)
		SynchPutString((char*)s);
	
	UserThreadExit();
}

int main () {	
	SynchPutString("Demarrage du main...\n");

	// Premier Thread
	void* f = afficheString;

    int res = UserThreadCreate(f,"s");
    res = UserThreadCreate(f,"z");
    /* not reached */
    return res;
}