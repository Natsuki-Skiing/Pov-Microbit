#include "pxt.h"
#include "MicroBit.h"
#include <vector>
#include <string>
#include <cstdint>




namespace shakeScreen {
class Pov {
private:
    std::vector<int8_t> messageIndexs;
    uint32_t rowMasks[5]; 
    uint8_t windowSize;
    bool looping;
    uint8_t completionCounter;
    bool messageComplete;
    bool shouldStop;
    const bool alpha[39][5][5] = {
            // 'A'
            {
                {false, true, true, true, true},  // Column 0
                {true, false, true, false, false}, // Column 1
                {true, false, true, false, false}, // Column 2
                {true, false, true, false, false}, // Column 3
                {false, true, true, true, true}    // Column 4
            },
            // 'B'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, true, false, true},  // Column 1
                {true, false, true, false, true},  // Column 2
                {true, false, true, false, true},  // Column 3
                {false, true, false, true, false}  // Column 4
            },
            // 'C'
            {
                {false, true, true, true, false},  // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, false, false, true}, // Column 2
                {true, false, false, false, true}, // Column 3
                {true, false, false, false, true}  // Column 4
            },
            // 'D'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, false, false, true}, // Column 2
                {false, true, true, true, false},  // Column 3
                {false, false, false, false, false} // Column 4
            },
            // 'E'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, true, false, true},  // Column 1
                {true, false, true, false, true},  // Column 2
                {true, false, true, false, true},  // Column 3
                {true, false, false, false, true}  // Column 4
            },
            // 'F'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, true, false, false}, // Column 1
                {true, false, true, false, false}, // Column 2
                {true, false, false, false, false}, // Column 3
                {true, false, false, false, false} // Column 4
            },
            // 'G'
            {
                {false, true, true, true, false},  // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, true, false, true},  // Column 2
                {true, false, true, false, true},  // Column 3
                {true, false, true, true, false}   // Column 4
            },
            // 'H'
            {
                {true, true, true, true, true},    // Column 0
                {false, false, true, false, false}, // Column 1
                {false, false, true, false, false}, // Column 2
                {false, false, true, false, false}, // Column 3
                {true, true, true, true, true}     // Column 4
            },
            // 'I'
            {
                {true, false, false, false, true}, // Column 0
                {true, false, false, false, true}, // Column 1
                {true, true, true, true, true},    // Column 2
                {true, false, false, false, true}, // Column 3
                {true, false, false, false, true}  // Column 4
            },
            // 'J'
            {
                {true, false, false, false, false}, // Column 0
                {true, false, false, false, false}, // Column 1
                {true, true, true, true, true},     // Column 2
                {true, false, false, false, false}, // Column 3
                {false, true, false, true, false}   // Column 4
            },
            // 'K'
            {
                {true, true, true, true, true},    // Column 0
                {false, false, true, false, false}, // Column 1
                {false, true, false, true, false}, // Column 2
                {true, false, false, false, true}, // Column 3
                {false, false, false, false, false} // Column 4
            },
            // 'L'
            {
                {true, true, true, true, true},    // Column 0
                {false, false, false, false, true}, // Column 1
                {false, false, false, false, true}, // Column 2
                {false, false, false, false, true}, // Column 3
                {false, false, false, false, true}  // Column 4
            },
            // 'M'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, false, false, false}, // Column 1
                {false, true, false, true, false}, // Column 2
                {true, false, false, false, false}, // Column 3
                {true, true, true, true, true}     // Column 4
            },
            // 'N'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, false, false, false}, // Column 1
                {false, true, false, false, false}, // Column 2
                {false, false, true, false, false}, // Column 3
                {true, true, true, true, true}     // Column 4
            },
            // 'O'
            {
                {false, true, true, true, false},  // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, false, false, true}, // Column 2
                {true, false, false, false, true}, // Column 3
                {false, true, true, true, false}   // Column 4
            },
            // 'P'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, false, false, false}, // Column 1
                {true, false, false, false, false}, // Column 2
                {true, false, false, false, false}, // Column 3
                {false, true, false, false, false} // Column 4
            },
            // 'Q'
            {
                {false, true, true, true, false},  // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, true, false, true},  // Column 2
                {true, false, false, true, false}, // Column 3
                {false, true, true, false, true}   // Column 4
            },
            // 'R'
            {
                {true, true, true, true, true},    // Column 0
                {true, false, false, false, false}, // Column 1
                {true, false, false, false, false}, // Column 2
                {true, false, false, true, false}, // Column 3
                {false, true, true, false, true}   // Column 4
            },
            // 'S'
            {
                {false, true, false, false, true}, // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, true, false, true},  // Column 2
                {true, false, false, false, true}, // Column 3
                {true, false, false, true, false}  // Column 4
            },
            // 'T'
            {
                {true, false, false, false, false}, // Column 0
                {true, false, false, false, false}, // Column 1
                {true, true, true, true, true},     // Column 2
                {true, false, false, false, false}, // Column 3
                {true, false, false, false, false}  // Column 4
            },
            // 'U'
            {
                {true, true, true, true, false},   // Column 0
                {false, false, false, false, true}, // Column 1
                {false, false, false, false, true}, // Column 2
                {false, false, false, false, true}, // Column 3
                {true, true, true, true, false}    // Column 4
            },
            // 'V'
            {
                {true, true, false, false, false}, // Column 0
                {false, false, true, false, false}, // Column 1
                {false, false, false, true, false}, // Column 2
                {false, false, true, false, false}, // Column 3
                {true, true, false, false, false}  // Column 4
            },
            // 'W'
            {
                {true, true, true, true, true},    // Column 0
                {false, false, false, false, true}, // Column 1
                {false, false, true, false, false}, // Column 2
                {false, false, false, false, true}, // Column 3
                {true, true, true, true, true}     // Column 4
            },
            // 'X'
            {
                {true, true, false, true, true},   // Column 0
                {false, false, true, false, false}, // Column 1
                {false, false, true, false, false}, // Column 2
                {false, false, true, false, false}, // Column 3
                {true, true, false, true, true}    // Column 4
            },
            // 'Y'
            {
                {true, true, false, false, false}, // Column 0
                {false, false, true, false, false}, // Column 1
                {false, false, false, true, false}, // Column 2
                {false, false, true, false, false}, // Column 3
                {true, true, false, false, false}  // Column 4
            },
            // 'Z'
            {
                {true, false, false, true, true},  // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, true, false, true},  // Column 2
                {true, false, false, false, true}, // Column 3
                {true, true, false, false, true}   // Column 4
            },
            // Numbers
            // 0
            {
                {false, true, true, true, false},  // Column 0: Left curve
                {true, false, false, false, true}, // Column 1: Top/bottom curves
                {true, false, false, false, true}, // Column 2: Sides
                {true, false, false, false, true}, // Column 3: Top/bottom curves
                {false, true, true, true, false}   // Column 4: Right curve
            },
            // 1
            {
                {false, false, false, false, false}, // Column 0: Empty
                {false, true, false, false, true},   // Column 1: Left edge
                {true, true, true, true, true},      // Column 2: Center stem
                {false, false, false, false, true},  // Column 3: Base extension
                {false, false, false, false, false}  // Column 4: Empty
            },
            // 2
            {
                {false, true, false, false, true},   // Column 0: Top curve + base
                {true, false, false, false, true},   // Column 1: Top-right + base
                {true, false, false, true, true},    // Column 2: Middle diagonal
                {true, false, true, false, true},    // Column 3: Upper-mid diagonal
                {false, true, false, false, true}    // Column 4: Top + base line
            },
            // 3
            {
                {false, true, false, false, true},   // Column 0: Outer edges
                {true, false, true, false, true},    // Column 1: Gaps + ends
                {true, false, true, false, true},    // Column 2: Middle bar + ends
                {true, false, true, false, true},    // Column 3: Gaps + ends
                {false, true, false, true, false}    // Column 4: Right curves
            },
            // 4
            {
                {false, false, true, true, false},   // Column 0: Top diagonal
                {false, true, false, true, false},   // Column 1: Diagonal continues
                {true, false, false, true, false},   // Column 2: Diagonal + crossbar
                {true, true, true, true, true},      // Column 3: Vertical line
                {false, false, false, true, false}   // Column 4: Crossbar extension
            },
            // 5
            {
                {true, true, true, true, true},      // Column 0: Left vertical
                {true, false, true, false, true},    // Column 1: Top bar + middle + bottom
                {true, false, true, false, true},    // Column 2: Top bar + middle + bottom
                {true, false, false, false, true},   // Column 3: Top bar + bottom
                {true, false, false, true, false}    // Column 4: Top + bottom curve
            },
            // 6
            {
                {false, true, true, true, false},    // Column 0: Left curve
                {true, false, true, false, true},    // Column 1: Top gap + middle + bottom
                {true, false, true, false, true},    // Column 2: Top gap + middle + bottom
                {true, false, true, false, true},    // Column 3: Top gap + middle + bottom
                {false, false, false, true, false}   // Column 4: Bottom curve
            },
            // 7
            {
                {true, false, false, false, false},  // Column 0: Top bar
                {true, false, false, false, false},  // Column 1: Top bar
                {true, false, false, true, true},    // Column 2: Top bar + diagonal
                {true, false, true, false, false},   // Column 3: Top bar + diagonal
                {true, true, false, false, false}    // Column 4: Top bar + diagonal
            },
            // 8
            {
                {false, true, true, true, false},    // Column 0: Left curves
                {true, false, true, false, true},    // Column 1: Top/middle/bottom gaps
                {true, false, true, false, true},    // Column 2: Top/middle/bottom gaps
                {true, false, true, false, true},    // Column 3: Top/middle/bottom gaps
                {false, true, true, true, false}     // Column 4: Right curves
            },
            // 9
            {
                {false, true, false, false, false},  // Column 0: Top curve
                {true, false, true, false, true},    // Column 1: Top + middle + bottom
                {true, false, true, false, true},    // Column 2: Top + middle + bottom
                {true, false, true, false, true},    // Column 3: Top + middle + bottom
                {false, true, true, true, false}     // Column 4: Right vertical
            },
            // !
            {
                {false, false, false, false, false}, // Column 0
                {false, false, false, false, false}, // Column 1
                {true, true, true, false, true},     // Column 2: Stem + Dot
                {false, false, false, false, false}, // Column 3
                {false, false, false, false, false}  // Column 4
            },
            // @
            {
                {false, true, true, true, false},    // Column 0: Outer Left
                {true, false, false, false, true},   // Column 1: Top/Bot
                {true, false, true, true, true},     // Column 2: Inner 'a' structure
                {true, false, true, false, true},    // Column 3: Inner 'a' structure
                {false, true, false, false, true}    // Column 4: Outer Right wrap
            },
            // #
            {
                {false, true, false, true, false},   // Column 0: Horizontal bars
                {true, true, true, true, true},      // Column 1: Vertical line
                {false, true, false, true, false},   // Column 2: Horizontal bars
                {true, true, true, true, true},      // Column 3: Vertical line
                {false, true, false, true, false}    // Column 4: Horizontal bars
            }
            };
            

    volatile bool messagePending;
    std::string pendingMessage;
    std::vector<std::vector<bool>> wholeMessage;
    void prepareWholeMessage();
    void getAlphaIndexes(const char* message, uint8_t lenght);
    void clearLEDS();
    void setLEDS(std::vector<bool> colData);

public:
    Pov(std::string message);
    void updateMessage(std::string s);
    void displayPov();
    void stop();
    uint8_t getNumberOfLetters();
    void setNumberOfLetters(uint8_t noLetters);
    void setLooping(bool looping);
    bool getLooping();

};}