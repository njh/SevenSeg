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

void SevenSeg::write(const char buf[], uint8_t len) {
    digitalWrite(this->slaveSelectPin, LOW);
    delay(30);
    for(int i=0; i<len; i++) {
        SPI.transfer(buf[i]);
    }
    digitalWrite(this->slaveSelectPin, HIGH);
}

void SevenSeg::reset() {
    char buf[1] = {0x76};
    write(buf, 1);
}

void SevenSeg::brightness(uint8_t value) {
    char buf[2] = {0x7A, value};
    write(buf, 2);
}

void SevenSeg::display(char dig1, char dig2, char dig3, char dig4) {
    char buf[4] = {dig1, dig2, dig3, dig4};
    write(buf, 4);
}

void SevenSeg::display(const char digits[4]) {
    write(digits, 4);
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

void SevenSeg::setDigit(uint8_t position, uint8_t value)
{
    char buf[2] = {0x7A+position, value};
    write(buf, 2);
}

void SevenSeg::setDigits(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4)
{
    char buf[8] = {0x7B, dig1, 0x7C, dig2, 0x7D, dig3, 0x7E, dig4};
    write(buf, 8);
}

void SevenSeg::setDecimalPoint(uint8_t value)
{
    char buf[2] = {0x77, value};
    write(buf, 2);
}

void SevenSeg::printError(void) {
    write("oUER", 4);
}
