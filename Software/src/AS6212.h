#ifndef AS6212_h
#define AS6212_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

class AS6212
{
  public:
    bool begin(uint8_t deviceAddress = 0x__, TwoWire &wirePort = Wire);
    float readTempC(void);
    float readTempF(void);
    void sleep(void);
    void wakeup(void);
    bool alert(void);
    void setLowTemp(float temperature);
    void setHighTemp(float temperature);
    void singleShotRead(void);
    
    // Set the conversion rate (0-3)
    // 0 - 0.25 Hz
    // 1 - 1 Hz
    // 2 - 4 Hz (default)
    // 3 - 8 Hz
    void setConversionRate(uint8_t rate);

    // Set the polarity of Alert
    // 0 - Active LOW
    // 1 - Active HIGH
    void setAlertPolarity(bool polarity);

    // Set the number of consecutive faults
    // 0 - 1 fault
    // 1 - 2 faults
    // 2 - 4 faults
    // 3 - 6 faults
    void setFault(uint8_t faultSetting);

    
  private:
    TwoWire *_i2cPort;
    int _address;

    void openPointerRegister(uint8_t pointerReg);
    uint8_t readRegister(bool registerNumber);
};

#endif
