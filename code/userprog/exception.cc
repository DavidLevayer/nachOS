// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#ifdef CHANGED
#include "userthread.h"
#include "fork.h"
#endif

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);
#ifndef CHANGED 
    if ((which == SyscallException) && (type == SC_Halt))
      {
	  DEBUG ('a', "Shutdown, initiated by user program.\n");
	  interrupt->Halt ();
      }
    else
      {
	  printf ("Unexpected user mode exception %d %d\n", which, type);
	  ASSERT (FALSE);
      }
#else //CHANGED
      if(which == SyscallException){
        switch(type){
          case SC_Halt:{
            DEBUG('a', "Shutdown, initiated by user program.\n");
            while(currentThread->space->NbreThread()>1) // tant qu'il y a plus que un thread on reste bloquer
              currentThread->space->LockEndMain();
            
            interrupt->Halt();
            break;
          }
          case SC_Exit:{ // cas appelé lors d'un fin de programme sans appel à la fonction Halt()
            //int valRetour = machine->ReadRegister(2); // registre contenant la valeur de retour
            break;
          }
          case SC_Yield:{
            break;
          }
          case SC_PutChar:{
            int c = machine->ReadRegister(4); // registre contenant le parametre de la fonction appelée
            DEBUG('a',"appel de la fonction SynchPutChar\n");
            synchconsole->SynchPutChar((char)c);
            DEBUG('a',"\nfin d'appel en mode kernel\n");
            break;
          }
          case SC_SynchPutString:{
            int c = machine->ReadRegister (4); // recupération de la chaine de caractère
            char* to = new char[MAX_STRING_SIZE+1]; // buffer le +1 permet d'ajouter le caractere de fin de chaine
            synchconsole->CopyStringFromMachine(c, to, MAX_STRING_SIZE); // copie chaine mips vers chaine Linux
            DEBUG('a',"appel système de la fonction SynchPutString\n");
            synchconsole->SynchPutString(to);
            delete [] to; //desallocation du buffer
            break;
          }
          case SC_SynchGetChar:{
            char c = synchconsole->SynchGetChar();
            //printf("%c",c);
            machine->WriteRegister(2,(int)c); // ecriture dans le registre 2 du résultat de la fonction
            break;
          }
          case SC_SynchGetString:{
            int to = machine->ReadRegister(4);
            int taille = machine->ReadRegister(5); //recuperation du 2eme param de la fonction SynchGetString
            char* from = new char[taille];
            synchconsole->SynchGetString(from,taille-1);
            synchconsole->CopyMachineFromString(from,to,taille); //copie de chaine linux vers chaine mips 
            delete [] from;
            break;
          }
          case SC_SynchPutInt:{
            int entier = machine->ReadRegister(4);
            synchconsole->SynchPutInt(entier);
            break;
          }
          case SC_SynchGetInt:{
            int* n = new int;
            *n = machine->ReadRegister(4);
            synchconsole->SynchGetInt(n);
            delete n;
            break;
          }
          case SC_UserThreadCreate:{
            int addrFunction = machine->ReadRegister(4);
            int addrArgs = machine->ReadRegister(5);
            int result = do_UserThreadCreate(addrFunction, addrArgs);
            machine->WriteRegister(2,result);
            break;
          }
          case SC_UserThreadExit:{
            do_UserThreadExit();
            break;
          }
          case SC_UserThreadJoin:{
            int idThread = machine->ReadRegister(4);
            do_UserThreadJoin(idThread);
            break;
          }
          case SC_ForkExec:{
            printf("exception forkex\n");
            int arg = machine->ReadRegister(4);
            char* to = new char[MAX_STRING_SIZE+1]; // buffer le +1 permet d'ajouter le caractere de fin de chaine
            synchconsole->CopyStringFromMachine(arg, to, MAX_STRING_SIZE);
            do_UserFork(to);
            break;
          }
          default :{
            printf("Unexpected user mode exception %d %d\n", which, type);
            ASSERT(FALSE);
            break;
          }
        }
      }
#endif // CHANGED
    // LB: Do not forget to increment the pc before returning!
    UpdatePC (); // génère un warning qui bloque la compilation si on le place avant le #endif
    // End of addition

}