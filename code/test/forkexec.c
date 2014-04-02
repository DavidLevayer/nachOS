#include "syscall.h"

int main()
{
   ForkExec("../build/userpages0");
   ForkExec("../build/makethreads");
   return 0;
}
