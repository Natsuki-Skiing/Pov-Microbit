#include "pxt.h"
#include "MicroBit.h"
#include "pov.h"

using namespace pxt;
using namespace codal;

namespace pov { 
    static Pov* povInstance = nullptr;
    //%
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
    

    // //%
    // void povUpdateMessage(String message) {
    //     if (povInstance) {
            
    //     }else{
            
    //     }
    // }
}