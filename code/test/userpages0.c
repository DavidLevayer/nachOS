#include "syscall.h"

void afficheString(char* s) {
	int nb = 10;
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
    SynchPutString("Fin du main\n");
    /* not reached */
    return res;
}