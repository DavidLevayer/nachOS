#ifdef CHANGED
#include "thread.h"
#include "synch.h"

extern int do_UserThreadCreate(int f, int arg);
void do_UserThreadExit();
void do_UserThreadJoin(int idThread);

#endif // CHANGED