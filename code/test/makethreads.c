#include "syscall.h"

void affiche(int i) {
	//SynchPutString("Demarrage d'un thread...\n");
	SynchPutInt(*(int*)i);
	//SynchPutString("\nFin du thread\n");
	UserThreadExit();
}

void afficheString(char* s) {
	//SynchPutString("Demarrage d'un thread...\n");
	SynchPutString((char*)s);
	//SynchPutString("\nFin du thread\n");
	UserThreadExit();
}


int main () {	
	
	SynchPutString("Demarrage du main...\n");
	// Premier Thread
	int i = 999;
	void* f = affiche;
    int res = UserThreadCreate(f,&i);

    SynchPutString("retour au main...\n");

    // Second Thread
	f = afficheString;
    res = UserThreadCreate(f,"coucou cousin\n");
    SynchPutString("retour au main\n");
    PutChar('c');

    f = affiche;
    res = UserThreadCreate(f,&i);

    SynchPutString("fin du main\n");
    /* not reached */
    return res;
}
