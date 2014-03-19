#include "syscall.h"

void affiche(int i) {
	SynchPutString("Demarrage d'un thread...\n");
	SynchPutInt(i);
	
	UserThreadExit();
}


int main () {	
	int i = 999;
	//void *f = SynchPutInt;
	SynchPutString("Demarrage du main...\n");
	void* f = affiche;
    int res = UserThreadCreate(f,&i);
    /* not reached */
    return res;
}
