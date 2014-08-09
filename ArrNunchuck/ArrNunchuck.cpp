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
