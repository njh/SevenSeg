//
// SparkFun Seven Segment serial display library
// By Nicholas Humfrey
//
// With help from this forum post:
// http://arduino.cc/forum/index.php?topic=64362.0
//
// License: http://unlicense.org/
//

#include <SPI.h>
#include "SevenSeg.h"

SevenSeg::SevenSeg(uint8_t slaveSelectPin) {
    this->slaveSelectPin = slaveSelectPin;
}

void SevenSeg::init() {
    pinMode(this->slaveSelectPin, OUTPUT);
    SPI.setBitOrder(MSBFIRST);
    // The maximum speed of the display is 250kHz
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin();

    // Reset and blank the display
    reset();
}

void SevenSeg::reset() {
    digitalWrite(this->slaveSelectPin, LOW);
    delay(30);
    SPI.transfer(0x76);
    digitalWrite(this->slaveSelectPin, HIGH);
}

void SevenSeg::brightness(uint8_t value) {
    command(0x7A, value);
}

void SevenSeg::command(uint8_t command, uint8_t data) {
    digitalWrite(this->slaveSelectPin, LOW);
    delay(30);
    SPI.transfer(command);
    SPI.transfer(data);
    digitalWrite(this->slaveSelectPin, HIGH);
}

void SevenSeg::display(char dig1, char dig2, char dig3, char dig4) {
    digitalWrite(this->slaveSelectPin, LOW);
    delay(30);
    SPI.transfer(dig1);
    SPI.transfer(dig2);
    SPI.transfer(dig3);
    SPI.transfer(dig4);
    digitalWrite(this->slaveSelectPin, HIGH);
}

void SevenSeg::display(int16_t num) {
    const uint8_t base = 10;
    char digit[4] = { 0, ' ', ' ', ' ' };
    if (num > 9999) {
        // Number is too big
        printError();
    } else if (num < -999) {
        // Number is too small
        printError();
    } else if (num < 0) {
        uint16_t place = 0;
        num = (num ^ -1) + 1; // pretend num is positive
        while ( num && place < 4 ) {
            if ( num > 0 ) digit[place++] = num%base;
            num /= base;
        }
        digit[place] = '-'; // place negative sign appropriately
        display(digit[3], digit[2], digit[1], digit[0]);
    } else {
        uint16_t place = 0;
        while ( num && place < 4 ) {
            if ( num > 0 ) digit[place++] = num%base;
            num /= base;
        }
        display(digit[3], digit[2], digit[1], digit[0]);
    }
}

void SevenSeg::printError(void) {
    display('o','U', 'E', 'R');
}
