#ifndef	SEVEN_SEG_H
#define SEVEN_SEG_H

#if ARDUINO >= 100
  #include <Arduino.h> // Arduino 1.0
#else
  #include <WProgram.h> // Arduino 0022
#endif

#include <SPI.h>
#include <stdint.h>


class SevenSeg {
private:
  uint8_t slaveSelectPin;

public:
  SevenSeg(uint8_t slaveSelectPin);
  
  void init();

  void command(uint8_t command, uint8_t data);
  
//  void display(char str[4]);
  void display(char dig1, char dig2, char dig3, char dig4);
  void display(uint16_t value);
  
  void brightness(uint8_t value);
  void reset();
  
};

#endif
