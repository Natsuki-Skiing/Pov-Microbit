#include "pxt.h"
#include "MicroBit.h"
#include "pov.h"

using namespace pxt;
using namespace codal;

namespace extension { 
    static Pov* povInstance = nullptr;
    
    //%
    void povShowMessage(String message) {
        if (povInstance) {
            delete povInstance;
        }
        
        
        
        
        ManagedString ms = MSTR(message); 

    
        Pov p(std::string(ms.toCharArray()));
        
        
        if (povInstance) {
            povInstance->displayPov();
        }
        
    }
    //%
    void povUpdateMessage(String message) {
        if (povInstance) {
            ManagedString ms = MSTR(message);
            std::string msg = std::string(ms.toCharArray());
            povInstance->updateMessage(msg);
        }
    }
}