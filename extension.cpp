#include "pxt.h"
#include "MicroBit.h"
#include "pov.h"

using namespace pxt;
using namespace codal;

namespace shakeScreen{ 
    static Pov* povInstance = nullptr;
    static bool looping = false;  // Default OFF
    
    //%
    void povStopMessage(){
        if(povInstance){
            povInstance->stop();
            delete povInstance;
            povInstance = nullptr;
        }
    }
    
    //%
    void povShowMessage(String message) {
        ManagedString ms = MSTR(message); 
        std::string msg = std::string(ms.toCharArray());
        
        if (povInstance) {
            // Update existing message
            povInstance->updateMessage(msg);
        } else {
            // Create new instance
            povInstance = new Pov(msg);
            povInstance->setLooping(looping);
            create_fiber([povInstance] {povInstance->displayPov();});
        }
    }

    //%
    void povSetLooping(bool value){
        looping = value;
        if(povInstance){
            povInstance->setLooping(value);
        }
    }

    //% 
    bool povIsLooping(){
        if(povInstance){
            return(povInstance->getLooping());
        }
        return(looping);
    }
    
    //%
    bool povIsRunning(){
        if(povInstance){
            return(true);
        }
        return(false);
    }

    //%
    void povSetNumberOfCharacters(int number){
        if(povInstance){
            povInstance->setNumberOfLetters(number);
        }
    }

    //%
    int povGetNumberOfCharacters(){
        if(povInstance){
            return povInstance->getNumberOfLetters();
        }
        return 3;  // Default value
    }
}