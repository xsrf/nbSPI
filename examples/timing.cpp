#include <Arduino.h>
#include <SPI.h>
#define NBSPI_TDBG_IO D2
#include "nbSPI.h"

uint8_t* buffer;
const uint8_t size = 140;

ICACHE_RAM_ATTR void isr() {
    NBSPI_TDBG_HIGH;
    SPI.writeBytes(buffer,80);
    NBSPI_TDBG_LOW;
    delayMicroseconds(5);
    nbSPI_writeBytes(buffer,80);
}

void setup() {
  buffer = (uint8_t*) calloc(size, sizeof(byte));
  for(uint16_t i=0; i<size; i++) buffer[i] = i;
  SPI.begin();
  SPI.setFrequency(8e6);
  pinMode(NBSPI_TDBG_IO, OUTPUT);
  timer1_attachInterrupt(isr);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(5*300); // 5 ticks per µs
}

void loop() {
  delay(1);
}

