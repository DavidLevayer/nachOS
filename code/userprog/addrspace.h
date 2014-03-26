// addrspace.h 
//      Data structures to keep track of executing user programs 
//      (address spaces).
//
//      For now, we don't keep any information about address spaces.
//      The user level CPU state is saved and restored in the thread
//      executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"

#ifdef CHANGED
  #define PagePerThread 2
  #include "bitmap.h"
  #include "synch.h"
#endif //CHANGED

#define UserStackSize		1024	// increase this as necessary!

class AddrSpace
{
  public:
    AddrSpace (OpenFile * executable);	// Create an address space,
    // initializing it with the program
    // stored in the file "executable"
    ~AddrSpace ();		// De-allocate an address space

    void InitRegisters ();	// Initialize user-level CPU registers,
    // before jumping to user code
    #ifdef CHANGED
   int BeginPointStack();
   void DealloateMapStack();

   void LockEndMain(); // methode qui sera appelé au moment où le main finira son execution afin de le bloquer 
                      // s'il y a encore des threads en cours d'execution
   void FreeEndMain(); //methode pour debloquer le semaphore bloquant le main
   void LockIdThread(int id); // methode appelée pour bloquer le thread courant en attendant qu'un thread d'id id finisse son exécution
   void FreeIdThread(int id); // methode appelée par le thread d'id id pour signifier qu'il a fini son execution

   int NbreThread();

   TranslationEntry* getPageTable();
   void setPageTable(TranslationEntry *t);
    #endif //CHANGED

    void SaveState ();		// Save/restore address space-specific
    void RestoreState ();	// info on a context switch 

  private:
      TranslationEntry * pageTable;	// Assume linear page table translation
    // for now!
    unsigned int numPages;	// Number of pages in the virtual 

    #ifdef CHANGED
    BitMap* bitmapThreadStack;
    Semaphore* lockEndMain;
    Semaphore* waitOtherThread[(int)(UserStackSize/(PagePerThread*PageSize))];
    #endif //CHANGED
    // address space
};

#endif // ADDRSPACE_H
