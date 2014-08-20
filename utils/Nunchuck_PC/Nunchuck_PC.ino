//----------------------------------------------------------------------
// Nunchuck_PC -- PC Nunchuck Driver
//
//  Later we will modify this code to save calibration data.
//
//  Based on ArduinoNunchukDemo.ino.
//
//----------------------------------------------------------------------
// ArduinoNunchukDemo.ino
//
// Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
// Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
//----------------------------------------------------------------------

#include <Wire.h>
#include <ArrNunchuck.h>

ArrNunchuck nunchuk;

void setup()
{
  Serial.begin(115200);
  nunchuk.init();
}

//----------------------------------------
// px -- print a justified number
//----------------------------------------

void px(int n)
{
  Serial.print(" ");
  Serial.print(n);
}

void px2(int a, int b)
{
  px(a);
  px(b);
}

void loop()
{
  nunchuk.update();

  Serial.print("n ");
  px(nunchuk.stickX);
  px(nunchuk.stickY);
  px(nunchuk.accelX);
  px(nunchuk.accelY);
  px(nunchuk.accelZ);
  px(nunchuk.buttonZ);
  px(nunchuk.buttonC);
  Serial.println();
}
