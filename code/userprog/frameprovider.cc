#ifdef CHANGED
//la politique d’allocation des cadres est complètement locale à cette classe.

#include "bitmap.h"
#include <strings.h>	

void FrameProvider::FrameProvider(int n){
	myFrame = new bitmap(n);
}

void FrameProvider::~FrameProvider(){
	delete myFrame;
}


/*récupérer un cadre libre et initia-
*lisé à 0 par la fonction bzero
*/
FrameProvider::GetEmptyFrame(){


    //bzero (machine->mainMemory, size);
}

/*libérer un cadre obtenu par GetEmptyFrame*/
FrameProvider::ReleaseFrame(){

}

/*demander combien de cadres restent disponibles*/
FrameProvider::NumAvailFrame(){

}


#endif //CHANGED