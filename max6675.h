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
  MAX6675( int8_t CS);
  MAX6675(int8_t CS,int8_t sclk , miso);

  double readCelsius(void);
  void setupMax6675(void);
  void setupMax6675(int8_t sclk , miso);
  double readFahrenheit(void);
  // For compatibility with older versions:
  double readFarenheit(void) { return readFahrenheit(); }
 private:
  int8_t  cs;
  int8_t sclk, miso;
  uint8_t spiread(void);
};
