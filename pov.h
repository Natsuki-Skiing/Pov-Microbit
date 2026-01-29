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
    bool messageComplete;
    
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
                {false, true, true, true, false},  // Column 0
                {true, false, false, false, true}, // Column 1
                {true, false, true, false, true}, // Column 2
                {true, false, false, false, true}, // Column 3
                {false, true, true, true, false}   // Column 4
            },
            //1
            {
                {false, false, false, false, false},  // Column 0
                {false, false, false, false, false}, // Column 1
                {false, false, false, false, false}, // Column 2
                {false, false, false, false, false}, // Column 3
                {false, false, false, false, false}   // Column 4
            },
            // 2
            {
                {false, true, false, false, true},  // Column 0: Start of top curve + Base
                {true, false, false, false, true},  // Column 1: Top curve + Base
                {true, false, true, false, true},   // Column 2: Top curve + Mid + Base
                {true, false, false, true, true},   // Column 3: Top curve + Diagonal + Base
                {false, true, true, false, false}   // Column 4: Right curve
            },
            // 3
            {
                {false, true, false, false, true},  // Column 0: Top/Bot tips
                {true, false, false, false, true},  // Column 1: Top/Bot curves
                {true, false, true, false, true},   // Column 2: Mid prongs
                {true, false, true, false, true},   // Column 3: Mid prongs
                {false, true, true, true, false}    // Column 4: Right curve spine
            },
            // 4
            {
                {false, false, true, true, false},  // Column 0: Diagonal top
                {false, true, false, true, false},  // Column 1: Diagonal mid
                {true, false, false, true, false},  // Column 2: Diagonal low
                {true, true, true, true, true},     // Column 3: Vertical Stem
                {false, false, false, true, false}  // Column 4: Horizontal bar overhang
            },
            // 5
            {
                {true, true, true, true, true},     // Column 0: Top bar + Left down + Bot curve
                {true, false, true, false, true},   // Column 1: Top bar + Mid + Bot
                {true, false, true, false, true},   // Column 2: Top bar + Mid + Bot
                {true, false, true, false, true},   // Column 3: Top bar + Mid + Bot
                {true, false, false, true, true}    // Column 4: Top start + Bot curve
            },
            // 6
            {
                {false, true, true, true, false},   // Column 0: Left spine
                {true, false, true, false, true},   // Column 1: Top/Bot curves
                {true, false, true, false, true},   // Column 2: Mid/Bot curves
                {true, false, true, false, true},   // Column 3: Mid/Bot curves
                {false, true, false, false, false}  // Column 4: Top loop closer
            },
            // 7
            {
                {true, false, false, false, false}, // Column 0: Top bar
                {true, false, false, false, false}, // Column 1: Top bar
                {true, false, false, true, false},  // Column 2: Top bar + Diagonal
                {true, false, true, false, false},  // Column 3: Top bar + Diagonal
                {true, true, false, false, false}   // Column 4: Top bar + Diagonal start
            },
            // 8
            {
                {false, true, true, true, false},   // Column 0: Left curves
                {true, false, true, false, true},   // Column 1: Top/Mid/Bot
                {true, false, true, false, true},   // Column 2: Top/Mid/Bot
                {true, false, true, false, true},   // Column 3: Top/Mid/Bot
                {false, true, true, true, false}    // Column 4: Right curves
            },
            // 9
            {
                {false, false, true, true, false},  // Column 0: Left top curve
                {true, false, true, false, true},   // Column 1: Top/Mid
                {true, false, true, false, true},   // Column 2: Top/Mid
                {true, false, true, false, true},   // Column 3: Top/Mid
                {false, true, true, true, false}    // Column 4: Right spine
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