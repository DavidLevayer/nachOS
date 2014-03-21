#include "syscall.h"

void affiche(int i) {
	SynchPutString("Demarrage d'un thread...\n");
	SynchPutInt(*(int*)i);
	SynchPutString("\nFin du thread\n");
	UserThreadExit();
}

void afficheString(char* s) {
	SynchPutString("Demarrage d'un thread...\n");
	SynchPutString((char*)s);
	SynchPutString("\nFin du thread\n");
	UserThreadExit();
}


int main () {	
	
	SynchPutString("Demarrage du main...\n");

	// Premier Thread
	int i = 999;
	void* f = affiche;
    int res = UserThreadCreate(f,&i);

    // Second Thread
	f = afficheString;
    res = UserThreadCreate(f,"coucou cousin");

    f = affiche;
    res = UserThreadCreate(f,&i);
    /* not reached */
    return res;
}
