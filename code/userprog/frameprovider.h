#ifdef CHANGED

#include "bitmap.h"
#include <strings.h>	


class FrameProvider {
public:
	void FrameProvider(int n);
	void ~FrameProvider();
	GetEmptyFrame();
	ReleaseFrame();
	NumAvailFrame();
};



#endif// CHANGED