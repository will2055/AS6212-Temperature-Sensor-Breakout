#include "AS6212.h"

#define TEMPERATURE_REGISTER 0x00
#define CONFIG_REGISTER 0x01
#define T_LOW_REGISTER 0x02
#define T_HIGH_REGISTER 0x03

bool AS6212::begin(uint8_t deviceAddress, TwoWire &wirePort){

    _address = deviceAddress;
    _i2cPort->beginTransmission(_address);

    uint8_t error = _i2cPort->endTransmission();

    if(error == 0){
      return true;
    }

    else return false;
}

void AS6212::openPointerRegister(uint8_t pointerReg){

  _i2cPort->beginTransmission(_address);
  _i2cPort->write(pointerReg);
  _i2cPort->endTransmission();
}

uint8_t AS6212::readRegister(bool registerNumber){
  
  uint8_t registerByte[2];

  _i2cPort->requestFrom(_address, 2);
  registerByte[0] = (_i2cPort->read());
  registerByte[1] = (_i2cPort->read());

  return registerByte[registerNumber];
}

float AS6212::readTempC(void){

  uint8_t registerByte[2];
  int16_t digitalTemp;

  openPointerRegister(TEMPERATURE_REGISTER);

  registerByte[0] = readRegister(0);
  registerByte[1] = readRegister(1);

  if(registerByte[0] == 0xFF && registerByte[1] == 0xFF) return NAN;

  if(registerByte[1]&0x01){
    
    digitalTemp = ((registerByte[0]) << 5) | (registerByte[1] >> 3);

    if(digitalTemp > 0xFFF){

      digitalTemp |= 0xE000;
    }
  }

  else{

    digitalTemp = ((registerByte[0]) << 4) | (registerByte[1] >> 4);

    if(digitalTemp > 0x7FF){

      digitalTemp |= 0xF000;
    }
  }

  return digitalTemp*0.0078125;
}

float AS6212::readTempF(void){

  return readTempC()*9.0/5.0+32.0;
}
