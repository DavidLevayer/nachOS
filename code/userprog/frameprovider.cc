#ifdef CHANGED
//la politique d’allocation des cadres est complètement locale à cette classe.

#include "bitmap.h"
#include <strings.h>	
#include "frameprovider.h"
#include "system.h"

FrameProvider::FrameProvider(int n){
	myFrame = new BitMap(n);
}

FrameProvider::~FrameProvider(){
	delete myFrame;
}


/*récupérer un cadre libre et initialisé à 0 par la fonction bzero*/
int FrameProvider::GetEmptyFrame(){
	int frame = myFrame->Find();
	ASSERT(frame!=-1)
	//on doit utiliser le symbole '&' car bzero à besoin d'une adresse
    bzero(&machine->mainMemory[frame*PageSize], PageSize);
    return frame;
}

/*libérer un cadre obtenu par GetEmptyFrame*/
void FrameProvider::ReleaseFrame(int n){
	//fonction presente dans bitmap.cc
	myFrame->Clear(n);
}

/*demander combien de cadres restent disponibles*/
int FrameProvider::NumAvailFrame(){
	//fonction presente dans bitmap.cc
	return myFrame->NumClear();
}

#endif //CHANGED