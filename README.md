Arduino Library to make easy to control the SparkFun 7-Segment Serial Display

* Yellow: http://www.sparkfun.com/products/9764
* Blue: http://www.sparkfun.com/products/9765
* Red: http://www.sparkfun.com/products/9766
* Green: http://www.sparkfun.com/products/9767

This library only supports using the SPI interface.

Datasheet:
http://www.sparkfun.com/datasheets/Components/LED/7-Segment/SFE-0012-DS-7segmentSerial-v41.pdf

License:
http://unlicense.org/



API Overview
------------

Display an integer number (-999 to 9999):

    void display(int16_t value);

Display a sequence of 4 characters:

    void display(char dig1, char dig2, char dig3, char dig4);

Display a string of 4 characters:

    void display(const char str[4]);

Set specific segments of a digit (using SEVENSEG_A, SEVENSEG_B, ... constants):

    void setDigit(uint8_t position, uint8_t value);

Set specific segments of all four digits at once:

    void setDigits(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4);

Turn on and off the decimal points (see datasheet for values):

    void setDecimalPoint(uint8_t value);

Set the brightness of the display:

    void brightness(uint8_t value);

Reset the display:

    void reset();



Example
-------

```C
#include <SPI.h>
#include <SevenSeg.h>

// 7 Segment display Slave Select connected to pin 10
SevenSeg sevenSeg(10);

void setup() {
  sevenSeg.init();
}

void loop() {
  uint16_t i;
  for (i=9999; i>0; i--) {
    sevenSeg.display(i);
    delay(1000);
  }
}
```
