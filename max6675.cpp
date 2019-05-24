// lib is already edit, do not using public lib for system. 
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include <util/delay.h>
#include <stdlib.h>
#include "max6675.h"

MAX6675::MAX6675( int8_t CS) {
  this->cs = CS;
  //define pin modes
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

MAX6675::MAX6675(int8_t CS,int8_t sclk , miso) {
  this->cs = CS;
  //define pin modes
  this->sclk = sclk;
  this->miso = miso;
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

void MAX6675::setupMax6675(int8_t sclk , miso) {
	this->sclk = sclk;
  this->miso = miso;
	pinMode(sclk, OUTPUT); 
	pinMode(miso, INPUT);
}

void MAX6675::setupMax6675() {
  this->sclk = sclkDefault;
  this->miso = misoDefault;
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);
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
