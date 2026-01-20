#include "pxt.h"
#include "MicroBit.h"
#include <vector>
#include <string>
#include <cstdint>





class Pov {
private:
    std::vector<int8_t> messageIndexs;
    uint32_t rowMasks[5]; 
    PovAccelerometer povAccelerometer;

    
    const bool alpha[26][5][5] = {
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
            }};

    volatile bool messagePending;
    std::string pendingMessage;
    std::vector<std::vector<bool>> wholeMessage;
    void prepareWholeMessage();
    void getAlphaIndexes(const char* message, int length);
    void clearLEDS();
    void setLEDS(std::vector<bool> colData);

public:
    Pov(std::string message);
    void updateMessage(std::string s);
    void displayPov();
};