#include "syscall.h"

int main()
{
   ForkExec("../build/userpages0");
   //ForkExec("../test/userpages1");
   return 0;
}
