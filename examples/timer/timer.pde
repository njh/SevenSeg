#include <SPI.h>
#include <SevenSeg.h>

// 7 Segment display Slave Select connected to pin 10
SevenSeg sevenSeg(10);

void setup() {
  sevenSeg.init();
  sevenSeg.setDecimalPoint(0x10);   // Just turn on the colon
}

void loop() {
  uint16_t m, s;
  for(m=0; m<60; m++) {
    for(s=0; s<60; s++) {
      sevenSeg.display(m/10, m%10, s/10, s%10);

      // Note: not accurate
      delay(970);
    }
  }
  
}