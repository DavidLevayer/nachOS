#ifdef CHANGED
//la politique d’allocation des cadres est complètement locale à cette classe.

#include "bitmap.h"
#include <strings.h>	
#include "system.h"

void FrameProvider::FrameProvider(int n){
	myFrame = new bitmap(n);
}

void FrameProvider::~FrameProvider(){
	delete myFrame;
}


/*récupérer un cadre libre et initialisé à 0 par la fonction bzero*/
int FrameProvider::GetEmptyFrame(){
	int frame = myFrame->find();
	ASSERT(frame!=-1)
	//on doit utiliser le symbole '&' car bzero à besoin d'une adresse
    bzero(&machine->mainMemory[frame*PageSize], PageSize);
}

/*libérer un cadre obtenu par GetEmptyFrame*/
void FrameProvider::ReleaseFrame(int n){
	//fonction presente dans bitmap.cc
	myFrame->Clear(n);
}

/*demander combien de cadres restent disponibles*/
int FrameProvider::NumAvailFrame(){
	//fonction presente dans bitmap.cc
	myFrame->NumClear();
}
#endif //CHANGED