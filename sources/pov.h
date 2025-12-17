#include "pxt.h"
#include "MicroBit.h"
#include <vector>
#include <string>
#include <cstdint>



class PovAccelerometer {
private:
    codal::NRF52Pin i2cSdaInt;
    codal::NRF52Pin i2cSclInt;
    codal::NRF52I2C i2cInt;

    int16_t readAxis(uint8_t reg);

public:
    PovAccelerometer();
    int16_t getX();
};

class Pov {
private:
    std::vector<int8_t> messageIndexs;
    uint32_t rowMasks[5]; 
    PovAccelerometer povAccelerometer;

    
    static const bool alpha[26][5][5];

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