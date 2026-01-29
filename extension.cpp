#include "pxt.h"
#include "MicroBit.h"
#include "pov.h"

using namespace pxt;
using namespace codal;

namespace shakeScreen{ 
    static Pov* povInstance = nullptr;
    static bool looping = false;
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
            povInstance->updateMessage(msg);
            
            // delete povInstance;
             // povInstance = nullptr;
        }else{
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

        return(false);
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
        return 0;
    }
}