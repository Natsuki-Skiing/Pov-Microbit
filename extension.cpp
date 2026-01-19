#include "pxt.h"
#include "MicroBit.h"
#include "pov.h"

using namespace pxt;
using namespace codal;

namespace extension { 
    static Pov* pPov = nullptr;
    //%
    //%
    void povShowMessage(String message) {
        if (povInstance) {
            delete povInstance;
        }
        
        // Convert MakeCode string to C++ string
        ManagedString ms(message);
        std::string msg = std::string(ms.toCharArray());
        
        povInstance = new Pov(msg);
        
        // Run displayPov in a fiber so it doesn't block
        create_fiber([](void* arg) {
            if (povInstance) {
                povInstance->displayPov();
            }
        });
    }
    //%
    void povUpdateMessage(String message) {
        if (povInstance) {
            ManagedString ms(message);
            std::string msg = std::string(ms.toCharArray());
            povInstance->updateMessage(msg);
        }
    }
}