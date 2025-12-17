#include "pxt.h"
#include "MicroBit.h"
#include "MicroBitDisplayCustom.h"

using namespace pxt;
using namespace codal;

namespace extension { 
    Pov* pPov = nullptr;
    void povFiberEntry(){
        if(pPov){
            pPov->displayLoop();
        }
    }


    void initPov(){
        uBit.display.disable();
        
        if(!pPov){
            pPov = new Pov("");
            create_fiber(povFiberEntry);
        }
    }


    void showString(String message){
        if(pPov){
            pPov->updateMessage(message);
        }
    }
}