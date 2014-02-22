#ifdef CHANGED
#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H
#include "copyright.h"
#include "utility.h"
#include "console.h"
class SynchConsole {
	public:
	SynchConsole(char *readFile, char *writeFile);
	// initialize the hardware console device
	~SynchConsole();
	// clean up console emulation
	void SynchPutChar(const char ch);
	char SynchGetChar();
	// Unix putchar(3S)
	// Unix getchar(3S)
	void SynchPutString(const char *s); // Unix puts(3S)
	void SynchGetString(char *s, int n);

	void SynchPutInt(int n);
	void SynchGetInt(int *n);

	void CopyStringFromMachine( int from, char *to, unsigned size);
	void CopyMachineFromString(char* from, int to, unsigned size);
	// Unix fgets(3S)
	private:
	Console *console;
	
};
#endif // SYNCHCONSOLE_H
#endif // CHANGED
