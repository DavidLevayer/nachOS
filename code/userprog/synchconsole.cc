#ifdef CHANGED
#include "copyright.h"
#include "console.h"
#include "system.h"
#include "synch.h"
#include "synchconsole.h"

#define NBREMAXCARACTENTIER 12 //entier signé --> -2 147 483 648 à 2 147 483 647 soit 11 caractères max avec le "-"

static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);

	// un seul processus autorisé à lire et écrire dans la console
	writeChar = new Semaphore("write char",1);
	readChar = new Semaphore("read char",1);

	writeString = new Semaphore("write string",1);
	readString = new Semaphore("read string",1);


	console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
}
SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
	delete writeChar;
	delete readChar;
	delete writeString;
	delete readString;
}
void SynchConsole::SynchPutChar(const char ch)
{
	writeChar->P();

	console->PutChar(ch);
	writeDone->P();

	writeChar->V();
}
char SynchConsole::SynchGetChar()
{
	readChar->P();

	readAvail->P();
	char c = console->GetChar();

	readChar->V();
	return c;
}
void SynchConsole::SynchPutString(const char s[])
{
	writeString->P();

	int i = 0;

	while(*(s+i)!='\0'){
		SynchPutChar(*(s+i));
		i++;
	}

	writeString->V();
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
	readString->P();

	int i = 0;
	char c;
	while((i<n)&&((c=SynchGetChar())!=EOF)&&(c!='\n')){
		*(s+i)=c;
		i++;
	}
	*(s+i) = '\0';

	readString->V();
}

void SynchConsole::SynchPutInt(int n){

	char* string = new char[NBREMAXCARACTENTIER];
	snprintf(string,NBREMAXCARACTENTIER,"%d",n); //ecrit n dans string 
	SynchPutString(string);

	delete [] string;
}

void SynchConsole::SynchGetInt( int *n){
	int* i = new int;
	char* string = new char[NBREMAXCARACTENTIER];
	SynchGetString(string,NBREMAXCARACTENTIER);
	sscanf(string,"%d",i);

	machine->WriteMem(*n,4,*i);
	delete [] string;
	delete i;
}

/*
*@param : from -> adresse physique vers la chaine mips
*/
void SynchConsole::CopyStringFromMachine( int from, char *to, unsigned size)
{
	unsigned i = 0;
	int res;

	while((i<size)&&(machine->ReadMem(from+i,1,&res))){
		*(to+i)= (char)res;
		i++;
	}
	*(to+i)='\0';

}

void SynchConsole::CopyMachineFromString(char* from, int to, unsigned size){
	unsigned i = 0;
	int res;

	while((i<size)&&(*(from+i)!='\0')){
		res = *(from+i);
		machine->WriteMem(to+i,1,res);
		i++;
	}
	machine->WriteMem(to+i,1,'\0');

}
#endif // CHANGED
