#include "syscall.h"

int main()
{
   ForkExec("../build/userpages0");
   //ForkExec("../build/userpages1");
   return 0;
}
