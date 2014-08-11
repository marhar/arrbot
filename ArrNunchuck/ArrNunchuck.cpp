//----------------------------------------------------------------------
// ArrNunchuck -- ArrBot Nunchuck Library
//
// Derived from ArduinoNunchuk by Gabriel Biaconi.
//
//----------------------------------------------------------------------
//
// ArduinoNunchuk.cpp - Improved Wii Nunchuk library for Arduino
//
// Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
//
// Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
//
// Based on the following resources:
//   http://www.windmeadow.com/node/42
//   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
//   http://wiibrew.org/wiki/Wiimote/Extension_Controllers
//
//----------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include "ArrNunchuck.h"

#define ADDRESS 0x52

void ArrNunchuck::init()
{
  Wire.begin();

  _sendByte(0x55, 0xF0);
  _sendByte(0x00, 0xFB);

  update();
}

//----------------------------------------------------------------------
// init2 -- alternate initialization sequence
// as per http://goo.gl/wQlZMD
//
// this almost makes alonso's work, except that buttonZ gives
// a 1 on both buttons.  same for alex's unit.  newest unit
// not at all.
//----------------------------------------------------------------------
void ArrNunchuck::init2()
{
  byte cnt;
  uint8_t ctrlr_type[6];

  Wire.begin();
            
  // init controller 
  delay(1);
  Wire.beginTransmission(0x52);      // device address
  Wire.write(0xF0);                    // 1st initialisation register
  Wire.write(0x55);                    // 1st initialisation value
  Wire.endTransmission();
  delay(1);
  Wire.beginTransmission(0x52);
  Wire.write(0xFB);                    // 2nd initialisation register
  Wire.write(0x00);                    // 2nd initialisation value
  Wire.endTransmission();
  delay(1);
            
  // read the extension type from the register block        
  Wire.beginTransmission(0x52);
  Wire.write(0xFA);                    // extension type register
  Wire.endTransmission();
  Wire.beginTransmission(0x52);
  Wire.requestFrom(0x52, 6);               // request data from controller
  for (cnt = 0; cnt < 6; cnt++) {
      if (Wire.available()) {
          ctrlr_type[cnt] = Wire.read(); // Should be 0x0000 A420 0101 for Classic Controller, 0x0000 A420 0000 for nunchuck
      }
  }
  Wire.endTransmission();
  delay(1);
            
  // send the crypto key (zeros), in 3 blocks of 6, 6 & 4.
  Wire.beginTransmission(0x52);
  Wire.write(0xF0);                    // crypto key command register
  Wire.write(0xAA);                    // sends crypto enable notice
  Wire.endTransmission();
  delay(1);
  Wire.beginTransmission(0x52);
  Wire.write(0x40);                    // crypto key data address
  for (cnt = 0; cnt < 6; cnt++) {
      Wire.write(0x00);                    // sends 1st key block (zeros)
  }
  Wire.endTransmission();
  Wire.beginTransmission(0x52);
  Wire.write(0x40);                    // sends memory address
  for (cnt = 6; cnt < 12; cnt++) {
      Wire.write(0x00);                    // sends 2nd key block (zeros)
  }
  Wire.endTransmission();
  Wire.beginTransmission(0x52);
  Wire.write(0x40);                    // sends memory address
  for (cnt = 12; cnt < 16; cnt++) {
      Wire.write(0x00);                    // sends 3rd key block (zeros)
  }
  Wire.endTransmission();
  delay(1);
  // end device init
}


void ArrNunchuck::update()
{
  int count = 0;
  int values[6];

  Wire.requestFrom(ADDRESS, 6);

  while(Wire.available())
  {
    values[count] = Wire.read();
    count++;
  }

  stickX = values[0];
  stickY = values[1];
  accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
  accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
  accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
  buttonZ = !((values[5] >> 0) & 1);
  buttonC = !((values[5] >> 1) & 1);

  _sendByte(0x00, 0x00);
}

void ArrNunchuck::_sendByte(byte data, byte location)
{
  Wire.beginTransmission(ADDRESS);

  Wire.write(location);
  Wire.write(data);

  Wire.endTransmission();

  delay(10);
}
