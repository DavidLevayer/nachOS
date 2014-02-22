#include "syscall.h"

int main(){
	
    int i;
    SynchGetInt(&i);
    //SynchPutInt(i); à décommenter si on veut voir que l'affectation de i fonctionne
    return 0;
}
