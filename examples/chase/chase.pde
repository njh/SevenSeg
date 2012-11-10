#include <SPI.h>
#include <SevenSeg.h>

// 7 Segment display Slave Select connected to pin 10
SevenSeg sevenSeg(10);

void setup() {
  sevenSeg.init();
}

void loop() {
  sevenSeg.setDigits(SEVENSEG_A, 0, 0, 0);
  delay(100);
  sevenSeg.setDigits(0, SEVENSEG_A, 0, 0);
  delay(100);
  sevenSeg.setDigits(0, 0, SEVENSEG_A, 0);
  delay(100);
  sevenSeg.setDigits(0, 0, 0, SEVENSEG_A);
  delay(100);
  sevenSeg.setDigits(0, 0, 0, SEVENSEG_B);
  delay(100);
  sevenSeg.setDigits(0, 0, 0, SEVENSEG_C);
  delay(100);
  sevenSeg.setDigits(0, 0, 0, SEVENSEG_D);
  delay(100);
  sevenSeg.setDigits(0, 0, SEVENSEG_D, 0);
  delay(100);
  sevenSeg.setDigits(0, SEVENSEG_D, 0, 0);
  delay(100);
  sevenSeg.setDigits(SEVENSEG_D, 0, 0, 0);
  delay(100);
  sevenSeg.setDigits(SEVENSEG_E, 0, 0, 0);
  delay(100);
  sevenSeg.setDigits(SEVENSEG_F, 0, 0, 0);
  delay(100);
}
