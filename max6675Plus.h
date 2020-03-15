// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class SubSPI
{
public:
	SubSPI::SubSPI(int8_t sclk, int8_t miso):m_sclk(sclk), m_miso(miso)
	{
		pinMode(m_sclk,OUTPUT);
		pinMode(m_miso,OUTPUT);
	}
	int8_t getSclk() const
	{
		return m_sclk;
	}
	int8_t getMiso() const
	{
		return m_miso;
	}

private:
	int8_t m_sclk, m_miso;
};

class MAX6675{
 public:

  MAX6675(int8_t cs, const SubSPI& SpiConfig):m_cs(cs),
  sclk(SpiConfig.getSclk()),
  miso(SpiConfig.getMiso())
 {
	  pinMode(m_cs,OUTPUT);
 }
  double readCelsius(void);
  double readFahrenheit(void);
  // For compatibility with older versions:
  double readFarenheit(void) { return readFahrenheit(); }
 private:
  int8_t m_cs;
  volatile int8_t sclk, miso;
  uint8_t spiread(void);
};
