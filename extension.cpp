#include "pxt.h"
#include "MicroBit.h"
#include "pov.h"

using namespace pxt;
using namespace codal;

namespace extension { 
    static Pov* pPov = nullptr;
    //%
    void povFiberEntry(){
        if(pPov){
            pPov->displayPov();
        }
    }

    //%
    void init_Pov(){
        uBit.display.disable();
        
        if(!pPov){
            pPov = new Pov("");
            create_fiber(povFiberEntry);
        }
    }

    //%
    void show_String(String message){
        if(pPov){
            pPov->updateMessage(message);
        }
    }
}