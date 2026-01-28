#include "pxt.h"
#include "MicroBit.h"
#include "pov.h"

using namespace pxt;
using namespace codal;

namespace pov { 
    static Pov* povInstance = nullptr;
    
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
        if (povInstance) {
            ManagedString ms = MSTR(message);
            std::string msg = std::string(ms.toCharArray());
            povInstance->updateMessage(msg);
            
            // delete povInstance;
            // povInstance = nullptr;
        }

        ManagedString ms = MSTR(message); 

        povInstance = new Pov(std::string(ms.toCharArray()));
        //povInstance = new Pov("hi"); //DEBUG
        
        
        if (povInstance) {
            create_fiber([povInstance] {povInstance->displayPov();});    
        }
        
    }

    //%
    void povSetLooping(bool value){
        if(povInstance){
            povInstance ->setLooping(value);
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

    // //% 
    // bool povIsLooping(){
    //     if(povInstance){
    //         return(povInstance->getLooping());
    //     }

    //     return(false);
    // }
    
    //%

    void povSetLoop(bool value){
        if(povInstance){
            povInstance->setLooping(value);
        }
    }
}