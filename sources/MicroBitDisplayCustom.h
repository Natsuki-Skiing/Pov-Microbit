/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef MICROBIT_DISPLAY_CUSTOM_H
#define MICROBIT_DISPLAY_CUSTOM_H

#include "NRF52LedMatrixCustom.h"

namespace codal {

/**
 * Class definition for MicroBitDisplay
 */
class MicroBitDisplayCustom : public NRF52LEDMatrixCustom, public AnimatedDisplay 
{

public:
  /**
   * Constructor.
   *
   * Create a software representation of the micro:bit's 5x5 LED matrix.
   * The display is initially blank.
   *
   * @param timer The timer instance allocated for the display.
   * @param map The mapping information that relates pin inputs/outputs to
   * physical screen coordinates.
   * @param id The id the display should use when sending events on the
   * MessageBus. Defaults to DEVICE_ID_DISPLAY.
   *
   * Note 1: We want to replace the current uBit.display instance with this
   * instance. We don't have access to the Codal source, so we resort to this
   * very ugly approach. We use a memcpy to replace the display instance with
   * this. As such, we need to implement some workarounds to ensure
   * compatibility.
   *
   * Note 2: Instead of the original MicroBitDisplay, we pass a reference
   * to the display timer. The original display class creates a new timer inline
   * in its constructor (which I believe should be addressed in future Codal
   * releases, it would have been better if the display timer was also managed
   * by the MicroBit class, similar to all other timers). As we are overriding
   * the MicroBitDisplay instance, the display timer has already ben allocated
   * and we can't do that twice (reallocating means we need to free the first
   * one first, but also deallocate the NRF_TIMER resources like interrupts).
   * However (please take this bit with a bit of caution), the timer instance
   * lives somewhere in the heap, so we can just keep it there. It's interupts
   * point to a function location in the MicroBitDisplay class, but since we're
   * only gonna override the content of the function, and not it's address /
   * location, all timer stuff keeps working. In other words, it is safe to just
   * ignore the timer (I hope). I have modified NRF53LedMatrixCustom to just
   * self-reference the timer in the constructor, so it doesn't matter what you
   * pass here. Not beautiful, but it seems to work fine.
   */
  MicroBitDisplayCustom(NRFLowLevelTimer &timer, const MatrixMap &map, uint16_t id = DEVICE_ID_DISPLAY);

  /**
   * Destructor.
   */
  ~MicroBitDisplayCustom();
};

} // namespace codal

#endif // MICROBIT_DISPLAY_CUSTOM_H
