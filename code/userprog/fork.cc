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
	Serialisation* restor = (Serialisation*) arg; // on restaure notre sérialisation 
	currentThread->space = restor->space; // on affecte le nouvel espace mémoir à notre nouveau processus
	currentThread->space->InitRegisters ();	// on réinitialise les registres
    currentThread->space->RestoreState ();	// on charge la table des pages des registres

    machine->Run ();		// on lance le processus
}

int do_UserFork(char *s){

	OpenFile *executable = fileSystem->Open (s);
    AddrSpace *space = new AddrSpace(executable); // création du nouvel espace mémoir du processus que l'on va mettre en place

    Thread* newThread = new Thread("newProcess"); // un processus est juste un thread avec un nouvel espace mémoir

    Serialisation* save = new Serialisation; // comme pour les threads, on sérialise l'espace mémoir qu'on souhaite affecter à notre processus
    save->space = space;

    newThread->Fork(StartProcess,(int)save); // on fork le processus père
    machine->SetNbProcess(machine->GetNbProcess()+1); // on incrémente de 1 le nbre de processus créé
    delete executable;
    currentThread->Yield(); // le processus père est mis en attente
	return 0;
}

#endif 
