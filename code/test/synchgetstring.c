#include "syscall.h"
#define tailleMaXChaine 8


int
main ()
{
	char s[tailleMaXChaine+1];
    SynchGetString(s,tailleMaXChaine+1);
    //SynchPutString(s); à décommenter si on veut voir si on a bien la chaine s qui a été correctement affectée
    /* not reached */
    return 0;
}
