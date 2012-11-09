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
