#ifdef CHANGED
#include "userthread.h"
#include "addrspace.h"
#include "system.h"

static void StartUserThread(int f){
	
	OpenFile* fichier = new OpenFile(f);
	AddrSpace* mySpace = new AddrSpace(fichier);
	mySpace->InitRegisters();
	machine->Run();
}

int do_UserThreadCreate(int f, int arg)
{
	Thread* newThread = new Thread("threadUser"); // sur l'appel system UserthreadCreat on crée un nouveau thread.

// le fork positionne automatiquement space à la même adresse que le processus père
// il faut maintenant récupéré arg dans le nouveau thread... ( il y a marqué serialisation dans le sujet peut être un indice... )
	newThread->Fork(StartUserThread,f);
	return 0;
}


void do_UserThreadExit()
{
	return;
}

#endif // CHANGED