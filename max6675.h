// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
 
#define sclkDefault 46
#define misoDefault 48
  
class MAX6675 {
 public:
  MAX6675(int8_t sclk , int8_t miso, int8_t numberMax6675);

  double readCelsius(void);
  double readFahrenheit(void);
  // For compatibility with older versions:
  double readFarenheit(void) { return readFahrenheit(); }
 private:
  int8_t numberMax6675;
  int8_t  cs[];
  int8_t sclk, miso;
  uint8_t spiread(void);
};
