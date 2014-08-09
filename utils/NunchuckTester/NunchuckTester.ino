////////////////////////////////////////////////////////////////////////
// NunchuckTester -- test your Nunchuck.
//
//  Thi


// This code is based on the excellent Ardui
////////////////////////////////////////////////////////////////////////
/*
 * ArduinoNunchukDemo.ino
 
 *
 * This code is based on Gabriel Biaconi's ArduinoNunchuk project.
 *
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 * tidied up an calibration limits
 */

#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 19200

ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{
  Serial.begin(BAUDRATE);
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

  if (nunchuk.analogX > maxgx) maxgx = nunchuk.analogX;
  if (nunchuk.analogY > maxgy) maxgy = nunchuk.analogY;
  if (nunchuk.accelX  > maxax) maxax = nunchuk.accelX;
  if (nunchuk.accelY  > maxay) maxay = nunchuk.accelY;
  if (nunchuk.accelZ  > maxaz) maxaz = nunchuk.accelZ;
  if (nunchuk.zButton > maxbz) maxbz = nunchuk.zButton;
  if (nunchuk.cButton > maxbc) maxbc = nunchuk.cButton;
 
  if (nunchuk.analogX < mingx) mingx = nunchuk.analogX;
  if (nunchuk.analogY < mingy) mingy = nunchuk.analogY;
  if (nunchuk.accelX  < minax) minax = nunchuk.accelX;
  if (nunchuk.accelY  < minay) minay = nunchuk.accelY;
  if (nunchuk.accelZ  < minaz) minaz = nunchuk.accelZ;
  if (nunchuk.zButton < minbz) minbz = nunchuk.zButton;
  if (nunchuk.cButton < minbc) minbc = nunchuk.cButton;
 
  px(nunchuk.analogX);
  px(nunchuk.analogY);
  px(nunchuk.accelX);
  px(nunchuk.accelY);
  px(nunchuk.accelZ);
  px(nunchuk.zButton);
  px(nunchuk.cButton);

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
