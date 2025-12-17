#include "pxt.h"
#include "MicroBit.h"
#include "MicroBitDisplayCustom.h"

using namespace pxt;
using namespace codal;

namespace POV{ 

    /**
     * Take over the default display.
     */ 
    //%
    void init_display() {
		// Stop any ongoing renderings and timers
        uBit.display.stopAnimation();
        uBit.display.disable();
        uBit.display.~MicroBitDisplay();

        // Override display
        // The provided timer is unused, but needs to exist already. It doesn't matter which one you provide
        //NRFLowLevelTimer displayTimer = NRFLowLevelTimer(NRF_TIMER4, TIMER4_IRQn);
        new (&uBit.display) MicroBitDisplayCustom(uBit.systemTimer, uBit.ledMatrixMap);
    }
}