#ifdef CHANGED
#include "userthread.h"
#include "system.h"

// la structure est mis dans le .cc pour éviter qu'elle ne soit utilisée en dehors de ce fichier
struct Serialisation{
	int function; // adresse du pointeur de fonction
	int arg; // adresse du pointeur des arguments
};

Semaphore *waitThread = new Semaphore("thread",0);

static void StartUserThread(int f){

	//récupération du pointeur de fonction et des arguments de celle-ci
	Serialisation* restor = (Serialisation*) f;

	// initialisation des registres à 0
	for(int i=0;i<NumTotalRegs;i++)
	{
		machine->WriteRegister(i,0);
	}

	
	ASSERT(restor!=NULL);
	ASSERT(restor->function!=0);
	ASSERT(restor->arg!=0);

	// pc sur l'adresse de la fonction
	machine->WriteRegister(PCReg,restor->function);
	//écriture dans le registre 4 des arguments de la fonction
	machine->WriteRegister(4,restor->arg);
	// next pc sur l'adresse de la prochaine instruction
	machine->WriteRegister(NextPCReg,restor->function+4);
	//initialisation du pointeur de pile
	// TODO

	int b = currentThread->space->BeginPointStack();
	machine->WriteRegister(StackReg,b);
	printf("beginPointStack=%d",b);
	machine->WriteRegister(StackReg,currentThread->space->BeginPointStack());
	machine->Run();
}

int do_UserThreadCreate(int f, int arg)
{
	Thread* newThread = new Thread("threadUser"); // sur l'appel system UserthreadCreat on crée un nouveau thread.
	currentThread->space->incActiveThread();
	if(newThread == NULL) {
		DEBUG('t',"error in do_UserThreadCreate: thread null");
		return -1;
	}

	// création de la structure pour pouvoir récupérer f et arg par la suite
	Serialisation* save = new Serialisation;
	save->function = f;
	save->arg = arg;
	// le fork positionne automatiquement space à la même adresse que le processus père

	newThread->Fork(StartUserThread,(int)save);
	waitThread->P();
	return 0;
}


void do_UserThreadExit()
{	
	//suppression de l'espace d'adressage du thread
	//delete currentThread->space;
	waitThread->V();
	//fin du thread
	currentThread->space->decActiveThread();
	currentThread->Finish ();
	//delete currentThread; // pas sûr que ce soit la meilleure des choses à faire
}

#endif // CHANGED