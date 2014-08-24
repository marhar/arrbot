//----------------------------------------------------------------------
// Nunchuck_PC -- PC Nunchuck Driver
//
//  Later we will modify this code to save calibration data.
//
// message types (from arduino):
//
// i -- init
// n -- nunchuck data
// v -- version
// c -- current calibration data
//
// message types (to arduino):
//
// reserved for writing calibration data
//
//----------------------------------------------------------------------
// Based on ArduinoNunchukDemo.ino by Gabriel Biancono:
// Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
// Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
//----------------------------------------------------------------------

#include <Wire.h>
#include <ArrNunchuck.h>

ArrNunchuck nunchuk;

unsigned long lastbip;

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

//----------------------------------------------------------------------
// print_version -- print version record
//----------------------------------------------------------------------
void print_version()
{
  // 0 version, header not yet finished
  Serial.println("v 1 0");
}

//----------------------------------------------------------------------
// print_init -- print "initialization" data
//----------------------------------------------------------------------
void print_init()
{
  // useful for pusing reset without starting gui
  delay(250);
  Serial.println("i");
  delay(250);
  Serial.println("i");
  delay(250);
  Serial.println("i");
}

//----------------------------------------------------------------------
// print_calib -- print current calibration data
//----------------------------------------------------------------------
void print_calib()
{
  // fake calibration data
  Serial.println("c 1,2,3,4,5");
}

//----------------------------------------------------------------------
// print_current -- print the current values of the nunchuck
//----------------------------------------------------------------------
void print_current()
{
  Serial.print("n");
  px(nunchuk.stickX);
  px(nunchuk.stickY);
  px(nunchuk.accelX);
  px(nunchuk.accelY);
  px(nunchuk.accelZ);
  px(nunchuk.buttonZ);
  px(nunchuk.buttonC);
  Serial.println();
}

//----------------------------------------------------------------------
void loop()
{
  nunchuk.update();
  
  unsigned long now = millis();
  
  if (now > lastbip + 3000) {
    // BUG: after 50 days you will stop getting these records
    print_version();
    print_calib();
    lastbip = now;
  }
  print_current();
}

//----------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  nunchuk.init();
  lastbip = millis();
  print_init();
  print_calib();
  print_version();
  
}

