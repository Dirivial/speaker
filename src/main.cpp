#include <Arduino.h>

const int DAC_PIN = 25;      // GPIO25 = DAC1

void setup() {
  // nothing special needed for DAC
}

void loop() {
  // 1 kHz-ish square/saw hybrid test tone using dacWrite
  for (int i = 0; i < 1000; i++) {
    dacWrite(DAC_PIN, 255);  // high
    delayMicroseconds(250);
    dacWrite(DAC_PIN, 0);    // low
    delayMicroseconds(250);
  }

  // 1 second of silence
  dacWrite(DAC_PIN, 128);    // mid-level (approx 0 V AC at amp input via cap)
  delay(1000);
}

