//----------------------------------------------------------------------
// NunchuckTester -- test your Nunchuck.
//
//  This code does two things:
//    -- shows the current value of your nunchuck controls
//    -- shows the min/max positions of your nunchuck controls
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
  Serial.begin(19200);
  nunchuk.init();
}

//----------------------------------------
// px -- print a justified number
//----------------------------------------

void px(int n)
{
  char *s;
  
  if      (n < 10)   s = "    ";
  else if (n < 100)  s = "   ";
  else if (n < 1000) s = "  ";
  else               s = " ";
  
  Serial.print(s);
  Serial.print(n);
}

void px2(int a, int b)
{
  px(a);
  px(b);
}

int mingx = 9999; int maxgx = -1;
int mingy = 9999; int maxgy = -1;
int minax = 9999; int maxax = -1;
int minay = 9999; int maxay = -1;
int minaz = 9999; int maxaz = -1;
int minbz = 9999; int maxbz = -1;
int minbc = 9999; int maxbc = -1;

void loop()
{
  nunchuk.update();

  if (nunchuk.stickX > maxgx) maxgx = nunchuk.stickX;
  if (nunchuk.stickY > maxgy) maxgy = nunchuk.stickY;
  if (nunchuk.accelX  > maxax) maxax = nunchuk.accelX;
  if (nunchuk.accelY  > maxay) maxay = nunchuk.accelY;
  if (nunchuk.accelZ  > maxaz) maxaz = nunchuk.accelZ;
  if (nunchuk.buttonZ > maxbz) maxbz = nunchuk.buttonZ;
  if (nunchuk.buttonC > maxbc) maxbc = nunchuk.buttonC;
 
  if (nunchuk.stickX < mingx) mingx = nunchuk.stickX;
  if (nunchuk.stickY < mingy) mingy = nunchuk.stickY;
  if (nunchuk.accelX  < minax) minax = nunchuk.accelX;
  if (nunchuk.accelY  < minay) minay = nunchuk.accelY;
  if (nunchuk.accelZ  < minaz) minaz = nunchuk.accelZ;
  if (nunchuk.buttonZ < minbz) minbz = nunchuk.buttonZ;
  if (nunchuk.buttonC < minbc) minbc = nunchuk.buttonC;
 
  px(nunchuk.stickX);
  px(nunchuk.stickY);
  px(nunchuk.accelX);
  px(nunchuk.accelY);
  px(nunchuk.accelZ);
  px(nunchuk.buttonZ);
  px(nunchuk.buttonC);

  Serial.print(" -");
  
  px2(mingx, maxgx);
  px2(mingy, maxgy);
  px2(minax, maxax);
  px2(minay, maxay);
  px2(minaz, maxaz);
  px2(minbz, maxbz);
  px2(minbc, maxbc);

  Serial.println();
}
