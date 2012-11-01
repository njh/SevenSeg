#include <SPI.h>
#include "SevenSeg.h"

SevenSeg::SevenSeg(uint8_t slaveSelectPin) {
	this->slaveSelectPin = slaveSelectPin;
}

void SevenSeg::init() {
	pinMode(this->slaveSelectPin, OUTPUT);
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV128);
	SPI.setDataMode(SPI_MODE0);
	SPI.begin();
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

// Changed param to signed integer from unsigned integer for negative numbers (2012-10-11 CCW)
void SevenSeg::display(int16_t num) {
	const uint8_t base = 10;
	char digit[4] = { 0, ' ', ' ', ' ' };
	if ( num>9999 ) {
		printError();
	}
	// Added check for negative numbers (2012-10-11 CCW)
	else if ( num < -999 ) {
		printError();
	}
	// Added support to display negative numbers (2012-10-11 CCW)
	else if(num < 0){
		uint16_t place = 0;
		num = (num ^ -1) + 1; //pretend num is positive
		while ( num && place < 4 ) {
			if ( num > 0 ) digit[place++] = num%base;
			num /= base;
		}
		digit[place] = '-'; // place negative sign appropriately
		display(digit[3], digit[2], digit[1], digit[0]);
	}
	else {
		uint16_t place = 0;
		while ( num && place < 4 ) {
			if ( num > 0 ) digit[place++] = num%base;
			num /= base;
		}
		display(digit[3], digit[2], digit[1], digit[0]);
	}
	
	
}

// Function for displaying error message (2012-10-11 CCW)
// Changed error message from "xxno" to "oUER"
void SevenSeg::printError(void) {
	display('o','U', 'E', 'R');
}