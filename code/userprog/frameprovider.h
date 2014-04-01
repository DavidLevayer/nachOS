#ifdef CHANGED

#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include "bitmap.h"
#include <strings.h>	

class FrameProvider {
public:
	FrameProvider(int n);
	~FrameProvider();
	int GetEmptyFrame();
	void ReleaseFrame(int n);
	int NumAvailFrame();
private:
	BitMap* myFrame;
};


#endif
#endif// CHANGED