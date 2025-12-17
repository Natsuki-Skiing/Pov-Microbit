#include "MicroBit.h"
#include "samples/Tests.h"
#include <vector>
#include <string>
#include <cstdint>
#include "CodalFiber.h"
#include "nrf_delay.h" 
#include "pov.h"
#define SHAKE_THRESHOLD  12000   
#define LETTER_DELAY_US  2000    
#define SPACE_DELAY_US   8000    
#define DARK_DELAY_US    200     


#define PORT0_OUT       (*(volatile uint32_t *)0x50000504)
#define PORT0_DIR       (*(volatile uint32_t *)0x50000514)



// Accelaromiter 
#define ACCEL_ADDR      (0x19 << 1) 
#define CTRL_REG1_A     0x20
#define OUT_X_L_A       0x28
#define CMD_AUTO_INC    0x80

//For longer messages, no shakes for the window to me moved 
#define SHAKES_MOVE_WIN 1
#define NO_LETTER -1
#define WINDOW_SIZE 20
#define NUMBER_OF_SPACERS 3
// Setup Serial for debugging 
NRF52Pin usbTx(ID_PIN_USBTX, MICROBIT_PIN_UART_TX, PIN_CAPABILITY_DIGITAL);
NRF52Pin usbRx(ID_PIN_USBRX, MICROBIT_PIN_UART_RX, PIN_CAPABILITY_DIGITAL);
NRF52Serial serial(usbTx, usbRx, NRF_UARTE0);

class PovAccelerometer {
private:
    NRF52Pin i2cSdaInt{ID_PIN_SDA, MICROBIT_PIN_INT_SDA, PIN_CAPABILITY_DIGITAL};
    NRF52Pin i2cSclInt{ID_PIN_SCL, MICROBIT_PIN_INT_SCL, PIN_CAPABILITY_DIGITAL};
    NRF52I2C i2cInt{i2cSdaInt, i2cSclInt, NRF_TWIM0};
    int16_t readAxis(uint8_t reg);

public:
    PovAccelerometer();
    int16_t getX();
};

PovAccelerometer::PovAccelerometer() {
    i2cInt.setFrequency(100000);
    
    uint8_t config[] = {CTRL_REG1_A, 0x57};
    i2cInt.write(ACCEL_ADDR, config, 2);
}

int16_t PovAccelerometer::readAxis(uint8_t reg) {
    uint8_t data[2];
    uint8_t cmd = reg | CMD_AUTO_INC;
    i2cInt.write(ACCEL_ADDR, &cmd, 1, true);
    i2cInt.read(ACCEL_ADDR, data, 2);
    return (int16_t)((data[1] << 8) | data[0]);
}

int16_t PovAccelerometer::getX() {
    return readAxis(OUT_X_L_A);
}

// class Pov {
// private:
//     std::vector<int8_t> messageIndexs;
//     std::vector<std::vector<bool>> wholeMessage;
//     // Faster
//     uint32_t rowMasks[5]; 
//     const bool alpha[26][5][5] = {
//                 // 'A'
//                 {
//                     {false, true, true, true, true},  // Column 0
//                     {true, false, true, false, false}, // Column 1
//                     {true, false, true, false, false}, // Column 2
//                     {true, false, true, false, false}, // Column 3
//                     {false, true, true, true, true}    // Column 4
//                 },
//                 // 'B'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, true, false, true},  // Column 1
//                     {true, false, true, false, true},  // Column 2
//                     {true, false, true, false, true},  // Column 3
//                     {false, true, false, true, false}  // Column 4
//                 },
//                 // 'C'
//                 {
//                     {false, true, true, true, false},  // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, false, false, false, true}, // Column 2
//                     {true, false, false, false, true}, // Column 3
//                     {true, false, false, false, true}  // Column 4
//                 },
//                 // 'D'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, false, false, false, true}, // Column 2
//                     {false, true, true, true, false},  // Column 3
//                     {false, false, false, false, false} // Column 4
//                 },
//                 // 'E'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, true, false, true},  // Column 1
//                     {true, false, true, false, true},  // Column 2
//                     {true, false, true, false, true},  // Column 3
//                     {true, false, false, false, true}  // Column 4
//                 },
//                 // 'F'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, true, false, false}, // Column 1
//                     {true, false, true, false, false}, // Column 2
//                     {true, false, false, false, false}, // Column 3
//                     {true, false, false, false, false} // Column 4
//                 },
//                 // 'G'
//                 {
//                     {false, true, true, true, false},  // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, false, true, false, true},  // Column 2
//                     {true, false, true, false, true},  // Column 3
//                     {true, false, true, true, false}   // Column 4
//                 },
//                 // 'H'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {false, false, true, false, false}, // Column 1
//                     {false, false, true, false, false}, // Column 2
//                     {false, false, true, false, false}, // Column 3
//                     {true, true, true, true, true}     // Column 4
//                 },
//                 // 'I'
//                 {
//                     {true, false, false, false, true}, // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, true, true, true, true},    // Column 2
//                     {true, false, false, false, true}, // Column 3
//                     {true, false, false, false, true}  // Column 4
//                 },
//                 // 'J'
//                 {
//                     {true, false, false, false, false}, // Column 0
//                     {true, false, false, false, false}, // Column 1
//                     {true, true, true, true, true},     // Column 2
//                     {true, false, false, false, false}, // Column 3
//                     {false, true, false, true, false}   // Column 4
//                 },
//                 // 'K'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {false, false, true, false, false}, // Column 1
//                     {false, true, false, true, false}, // Column 2
//                     {true, false, false, false, true}, // Column 3
//                     {false, false, false, false, false} // Column 4
//                 },
//                 // 'L'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {false, false, false, false, true}, // Column 1
//                     {false, false, false, false, true}, // Column 2
//                     {false, false, false, false, true}, // Column 3
//                     {false, false, false, false, true}  // Column 4
//                 },
//                 // 'M'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, false, false, false}, // Column 1
//                     {false, true, false, true, false}, // Column 2
//                     {true, false, false, false, false}, // Column 3
//                     {true, true, true, true, true}     // Column 4
//                 },
//                 // 'N'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, false, false, false}, // Column 1
//                     {false, true, false, false, false}, // Column 2
//                     {false, false, true, false, false}, // Column 3
//                     {true, true, true, true, true}     // Column 4
//                 },
//                 // 'O'
//                 {
//                     {false, true, true, true, false},  // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, false, false, false, true}, // Column 2
//                     {true, false, false, false, true}, // Column 3
//                     {false, true, true, true, false}   // Column 4
//                 },
//                 // 'P'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, false, false, false}, // Column 1
//                     {true, false, false, false, false}, // Column 2
//                     {true, false, false, false, false}, // Column 3
//                     {false, true, false, false, false} // Column 4
//                 },
//                 // 'Q'
//                 {
//                     {false, true, true, true, false},  // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, false, true, false, true},  // Column 2
//                     {true, false, false, true, false}, // Column 3
//                     {false, true, true, false, true}   // Column 4
//                 },
//                 // 'R'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {true, false, false, false, false}, // Column 1
//                     {true, false, false, false, false}, // Column 2
//                     {true, false, false, true, false}, // Column 3
//                     {false, true, true, false, true}   // Column 4
//                 },
//                 // 'S'
//                 {
//                     {false, true, false, false, true}, // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, false, true, false, true},  // Column 2
//                     {true, false, false, false, true}, // Column 3
//                     {true, false, false, true, false}  // Column 4
//                 },
//                 // 'T'
//                 {
//                     {true, false, false, false, false}, // Column 0
//                     {true, false, false, false, false}, // Column 1
//                     {true, true, true, true, true},     // Column 2
//                     {true, false, false, false, false}, // Column 3
//                     {true, false, false, false, false}  // Column 4
//                 },
//                 // 'U'
//                 {
//                     {true, true, true, true, false},   // Column 0
//                     {false, false, false, false, true}, // Column 1
//                     {false, false, false, false, true}, // Column 2
//                     {false, false, false, false, true}, // Column 3
//                     {true, true, true, true, false}    // Column 4
//                 },
//                 // 'V'
//                 {
//                     {true, true, false, false, false}, // Column 0
//                     {false, false, true, false, false}, // Column 1
//                     {false, false, false, true, false}, // Column 2
//                     {false, false, true, false, false}, // Column 3
//                     {true, true, false, false, false}  // Column 4
//                 },
//                 // 'W'
//                 {
//                     {true, true, true, true, true},    // Column 0
//                     {false, false, false, false, true}, // Column 1
//                     {false, false, true, false, false}, // Column 2
//                     {false, false, false, false, true}, // Column 3
//                     {true, true, true, true, true}     // Column 4
//                 },
//                 // 'X'
//                 {
//                     {true, true, false, true, true},   // Column 0
//                     {false, false, true, false, false}, // Column 1
//                     {false, false, true, false, false}, // Column 2
//                     {false, false, true, false, false}, // Column 3
//                     {true, true, false, true, true}    // Column 4
//                 },
//                 // 'Y'
//                 {
//                     {true, true, false, false, false}, // Column 0
//                     {false, false, true, false, false}, // Column 1
//                     {false, false, false, true, false}, // Column 2
//                     {false, false, true, false, false}, // Column 3
//                     {true, true, false, false, false}  // Column 4
//                 },
//                 // 'Z'
//                 {
//                     {true, false, false, true, true},  // Column 0
//                     {true, false, false, false, true}, // Column 1
//                     {true, false, true, false, true},  // Column 2
//                     {true, false, false, false, true}, // Column 3
//                     {true, true, false, false, true}   // Column 4
//                 }};

//     void getAlphaIndexes(const char *, int);
//     void setLEDS(std::vector<bool> );
//     void clearLEDS();

// public:
//     Pov(std::string);
//     void displayPov();
//     PovAccelerometer povAccelerometer{};
// };

Pov::Pov(std::string message) {
    
    updateMessage(message);

    rowMasks[0] = (1u << ROW_1);
    rowMasks[1] = (1u << ROW_2);
    rowMasks[2] = (1u << ROW_3);
    rowMasks[3] = (1u << ROW_4);
    rowMasks[4] = (1u << ROW_5);

    
    PORT0_DIR |= (rowMasks[0] | rowMasks[1] | rowMasks[2] | rowMasks[3] | rowMasks[4] | (1u << COL_3));
    
    // Start wil led off 
    clearLEDS();
}

void Pov::getAlphaIndexes(const char* message, int length) {
    for (int index = 0; index < length; index++) {
        char c = message[index];
        if (c >= 'a' && c <= 'z') c = toupper(c);
        if (c >= 'A' && c <= 'Z') {
            this->messageIndexs.push_back(c - 'A');
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
    
    // Set bits fro letter
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

    uint8_t messageLen;
    uint16_t msgNumberOfCols;
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
        int16_t x = povAccelerometer.getX();

        // Left to right x >= SHAKE_THRESHOLD
        if (x <= -SHAKE_THRESHOLD) {
            noShakes ++;
            
            for (int index = 0; index < WINDOW_SIZE; index++) {
                
               
              
                setLEDS(wholeMessage.at(((windowStart +index) % msgNumberOfCols)));
                nrf_delay_us(LETTER_DELAY_US);
                
                // Ghosting reduction
                clearLEDS(); 
                nrf_delay_us(DARK_DELAY_US);
                
                //nrf_delay_us(SPACE_DELAY_US);
            }
            
            
            clearLEDS();
            nrf_delay_ms(50); 
        } 
        // left to right x <= -SHAKE_THRESHOLD
        else if (x >= SHAKE_THRESHOLD) {
            noShakes ++;
            for (int index = WINDOW_SIZE; index >= 0; index--) {
                
                // columns  reverse order
                setLEDS(wholeMessage.at(((windowStart +index) % msgNumberOfCols)));
                nrf_delay_us(LETTER_DELAY_US);
                
                // Ghosting reduction
                clearLEDS(); 
                
                nrf_delay_us(DARK_DELAY_US);
                
                //nrf_delay_us(SPACE_DELAY_US);
            }
            
            clearLEDS();
            nrf_delay_ms(50);
        }
        // Scroll text
        if(noShakes == SHAKES_MOVE_WIN && messageLen > 3){
            windowStart ++;
            if((windowStart)>msgNumberOfCols){
                windowStart = 0;
            }
            noShakes = 0;
        }
        nrf_delay_us(100); 
    }
}

