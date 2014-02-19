#ifdef CHANGED

#include "copyright.h"
#include "console.h"
#include "system.h"
#include "synch.h"
#include "synchconsole.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
}
SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
}
void SynchConsole::SynchPutChar(const char ch)
{
	console->PutChar(ch);
	writeDone->P();
}
char SynchConsole::SynchGetChar()
{
	readAvail->P();
	return console->GetChar();
}
void SynchConsole::SynchPutString(const char s[])
{
	int i = 0;

	while(*(s+i)!='\0'){
		SynchPutChar(*(s+i));
		i++;
	}
}
void SynchConsole::SynchGetString(char *s, int n)
{
	
}

/*
*@param : from -> adresse physique vers la chaine mips
*/
void SynchConsole::CopyStringFromMachine( int from, char *to, unsigned size)
{
	unsigned i = 0;

	while((i<size)&&(machine->mainMemory[from+i]!='\0')){
		*(to+i)= machine->mainMemory[from+i];
		i++;
	}
	*(to+i)='\0';
}
#endif // CHANGED
