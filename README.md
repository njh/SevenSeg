Arduino Library to make easy to control the SparkFun 7-Segment Serial Display

* Yellow: http://www.sparkfun.com/products/9764
* Blue: http://www.sparkfun.com/products/9765
* Red: http://www.sparkfun.com/products/9766
* Green: http://www.sparkfun.com/products/9767


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
