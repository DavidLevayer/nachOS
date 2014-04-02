#ifdef CHANGED
#include "fork.h"
#include "thread.h"
#include "addrspace.h"
#include "synch.h"
#include "system.h"
#include "console.h"

struct Serialisation{
	AddrSpace* space;
};

void StartProcess(int arg){
	Serialisation* restor = (Serialisation*) arg;
	printf("coucou on est dans le fork\n");
	currentThread->space = restor->space;
	currentThread->space->InitRegisters ();	// set the initial register values
    currentThread->space->RestoreState ();	// load page table register

    machine->Run ();		// jump to the user progam
}

int do_UserFork(char *s){
	//printf("doudou\n");
	//char * s = (char*) arg;
	printf("on va ouvrir le fichier\n");
	OpenFile *executable = fileSystem->Open (s);
	printf("on a ouvert le fichier\n");
	//printf("%c\n",*(s+1));
    AddrSpace *space = new AddrSpace(executable);
    printf("on a créé la nouvelle addrspace \n");

    Thread* newThread = new Thread("newProcess");

    Serialisation* save = new Serialisation;
    save->space = space;
	printf("attention on va faire un fork\n");
    newThread->Fork(StartProcess,(int)save);

    delete executable;
    currentThread->Yield();
	return 0;
}

#endif 
