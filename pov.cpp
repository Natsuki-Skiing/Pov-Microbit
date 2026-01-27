#include "MicroBit.h"
#include <vector>
#include <string>
#include <cstdint>
#include "CodalFiber.h"
#include "nrf_delay.h" 
#include "pov.h"
#include "pxt.h"

#define SHAKE_THRESHOLD  1750   
#define LETTER_DELAY_US  2500    
#define SPACE_DELAY_US   8000    
#define DARK_DELAY_US    200     

#define PORT0_OUT       (*(volatile uint32_t *)0x50000504)
#define PORT0_DIR       (*(volatile uint32_t *)0x50000514)



#define SHAKES_MOVE_WIN 1
#define NO_LETTER -1
#define WINDOW_SIZE 20
#define NUMBER_OF_SPACERS 2


#define NUMBER_OF_CHARACTERS 36

// #define ROW_1 21
// #define ROW_2 22
// #define ROW_3 15
// #define ROW_4 24
// #define ROW_5 19
// #define COL_3 31




// Pov implementation
Pov::Pov(std::string message) :  messagePending(false) {
    uBit.display.clear();
    uBit.display.disable();
    updateMessage(message);

    rowMasks[0] = (1u << ROW_1);
    rowMasks[1] = (1u << ROW_2);
    rowMasks[2] = (1u << ROW_3);
    rowMasks[3] = (1u << ROW_4);
    rowMasks[4] = (1u << ROW_5);

    PORT0_DIR |= (rowMasks[0] | rowMasks[1] | rowMasks[2] | rowMasks[3] | rowMasks[4] | (1u << COL_3));
    
    clearLEDS();
}

void Pov::stop(){
    uBit.display.enable();
    uBit.display.clear();
}

void Pov::getAlphaIndexes(const char* message, uint8_t length) {
    static const std::string validCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#";

    for (uint8_t i = 0; i <length; i++) {
        char currentChar = message[i];

        
        
        currentChar = toupper(currentChar);
        

        size_t foundIndex = validCharacters.find(currentChar);
        if (foundIndex != std::string::npos) {
            this->messageIndexs.push_back(static_cast<int>(foundIndex));
        }
    }
}

void Pov::updateMessage(std::string s) {
    if(s.length() == 0) {
        return;
    }
    const char *Cmessage = s.c_str();
    this->messageIndexs.clear();
    getAlphaIndexes(Cmessage, s.length());
    this->messagePending = true;
}

void Pov::clearLEDS() {
    uint32_t current = PORT0_OUT;
    
    // rows off
    current &= ~(rowMasks[0] | rowMasks[1] | rowMasks[2] | rowMasks[3] | rowMasks[4]);
    
    // col 3 off 
    current |= (1u << COL_3);
    
    PORT0_OUT = current;
}

void Pov::setLEDS(std::vector<bool> colData) {
    uint32_t output = PORT0_OUT;
    
    output &= ~(rowMasks[0] | rowMasks[1] | rowMasks[2] | rowMasks[3] | rowMasks[4]);
    
    // Set bits for letter
    if(colData[0]) output |= rowMasks[0];
    if(colData[1]) output |= rowMasks[1];
    if(colData[2]) output |= rowMasks[2];
    if(colData[3]) output |= rowMasks[3];
    if(colData[4]) output |= rowMasks[4];

    output &= ~(1u << COL_3);

    PORT0_OUT = output;
}

void Pov::prepareWholeMessage() {
    this->messagePending = false;
    this->wholeMessage.clear();
    
    for(int index: this->messageIndexs){
        for(int col = 0; col < 5; col++) {
            std::vector<bool> columnData;
            for(int row = 0; row < 5; row++) {
                columnData.push_back(this->alpha[index][col][row]);
            }
            wholeMessage.push_back(columnData);
        }

        for(int s = 0; s < NUMBER_OF_SPACERS; s++) {
            wholeMessage.push_back({false, false, false, false, false});
        }
    }
}

void Pov::displayPov() {
    uint8_t messageLen = 0;
    uint8_t msgNumberOfCols = 0;
    uint8_t windowStart = 0;

    // number of shakes, used to time window movement
    int8_t noShakes = 0;

    while (true) {
        if(this->messagePending) {
            prepareWholeMessage();
            messageLen = this->messageIndexs.size();
            msgNumberOfCols = wholeMessage.size();
            windowStart = 0;
            noShakes = 0;
        }
        
        int16_t x = uBit.accelerometer.getX();

        // Left to right x >= SHAKE_THRESHOLD
        //x <= -SHAKE_THRESHOLD
        if (x <= -SHAKE_THRESHOLD) {
            noShakes++;
            
            for (int index = 0; index < WINDOW_SIZE; index++) {
                setLEDS(wholeMessage.at(((windowStart + index) % msgNumberOfCols)));
                nrf_delay_us(LETTER_DELAY_US);
                
                // Ghosting reduction
                clearLEDS(); 
                nrf_delay_us(DARK_DELAY_US);
            }
            
            clearLEDS();
            uBit.sleep(50);
        } 
        // right to left x <= -SHAKE_THRESHOLD
        else if (x >= SHAKE_THRESHOLD) {
            noShakes++;
            
            for (int index = WINDOW_SIZE-1; index >= 0; index--) {
                // columns reverse order
                setLEDS(wholeMessage.at(((windowStart + index) % msgNumberOfCols)));
                nrf_delay_us(LETTER_DELAY_US);
                
                // Ghosting reduction
                clearLEDS(); 
                nrf_delay_us(DARK_DELAY_US);
            }
            
            clearLEDS();
            uBit.sleep(50);
        }
        
        // Scroll text
        if(noShakes == SHAKES_MOVE_WIN && messageLen > 3){
            windowStart = (windowStart+1) %msgNumberOfCols;
            
            noShakes = 0;
        }
        
        uBit.sleep(100);
    }
}
