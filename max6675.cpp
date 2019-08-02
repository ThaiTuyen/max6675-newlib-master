// lib is already edit, do not using public lib for system. 
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include <util/delay.h>
#include <stdlib.h>
#include "max6675.h"



MAX6675::MAX6675(int8_t sclk , int8_t miso, int8_t numberMax6675)
{
  this->sclk = sclk;
  this->miso = miso;
  this->numberMax6675 = numberMax6675;
  pinMode(sclk,OUTPUT);
  pinMode(miso,OUTPUT);
}

void MAX6675::AddCSPin(int8_t listPin[this->numberMax6675-1])
{
	for (int index = 1; index <= numberMax6675;index++ )
	{
		this->cs[index] = listPin[index];
	}
}

double MAX6675::readCelsius(void) {

  uint16_t v;

  digitalWrite(cs, LOW);
  _delay_ms(1);

  v = spiread();
  v <<= 8;
  v |= spiread();

  digitalWrite(cs, HIGH);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    //return NAN; 
    return -100;
  }

  v >>= 3;

  return v*0.25;
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
