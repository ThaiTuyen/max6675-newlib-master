// lib is already edit, do not using public lib for system. 
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include <util/delay.h>
#include <stdlib.h>
#include "max6675Plus.h"


double MAX6675::readCelsius()
{
  uint16_t v;
  digitalWrite(m_cs, LOW);
  _delay_ms(1);
  v = spiread();
  v <<= 8;
  v |= spiread();
  digitalWrite(m_cs, HIGH);
  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    //return NAN; 
    return NAN;
  }
  v >>= 3;
  return double(v*0.25);
}

double MAX6675::readFahrenheit(void) {
  return readCelsius() * 9.0/5.0 + 32;
}

byte MAX6675::spiread(void) { 
  int i;
  byte d = 0;
  for (i=7; i>=0; i--)
  {
    digitalWrite(sclk, LOW);
    _delay_ms(1);
    if (digitalRead(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }
    digitalWrite(sclk, HIGH);
    _delay_ms(1);
  }
  return d;
}
