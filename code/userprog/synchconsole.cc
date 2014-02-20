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
/*
* fonction fait sur le modele de la fonction noyau fgets 
"fgets() reads in at most one less than size characters from stream and stores them into the buffer pointed to by s.  Reading stops after an
       EOF  or  a newline.  If a newline is read, it is stored into the buffer.  A terminating null byte ('\0') is stored after the last character
       in the buffer."
D'après le man.
*/
void SynchConsole::SynchGetString(char *s, int n)
{
	int i = 0;
	char c;
	while((i<n)&&((c=SynchGetChar())!=EOF)&&(c!='\n')){
		*(s+i)=c;
		i++;
	}
	*(s+i) = '\0';
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

void SynchConsole::CopyMachineFromString(char* from, int to, unsigned size){
	unsigned i = 0;

	while((i<size)&&(*(from+i)!='\0')){
		machine->mainMemory[to+i]=*(from+i);
		i++;
	}
	machine->mainMemory[to+i]='\0';
}
#endif // CHANGED
