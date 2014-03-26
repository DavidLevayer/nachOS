#ifdef CHANGED

#include "bitmap.h"
#include <strings.h>	


class FrameProvider {
public:
	void FrameProvider(int n);
	void ~FrameProvider();
	int GetEmptyFrame();
	void ReleaseFrame(int n);
	int NumAvailFrame();
};



#endif// CHANGED