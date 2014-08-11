#include "ArrServos.h"

//----------------------------------------------------------------------
// init -- initialize with some reasonable values (1000/1500/2000)
//----------------------------------------------------------------------
void arrbot_servocfg::init() {
  this->mid = 1500;
  this->span = 500;
  this->reverse = 1;
}

//----------------------------------------------------------------------
// attach -- just like Servo::attach, but includes calibration data
//----------------------------------------------------------------------
void arrbot_servo::attach(int pin, arrbot_servocfg* pc)
{
  myservo.attach(pin);
  mycfg = pc;
  mythrust = 0;
}

//----------------------------------------------------------------------
// thrust -- set the percentage for the motor, -100% .. 100%
//----------------------------------------------------------------------
void arrbot_servo::thrust(int t)
{
  int lo;       // low value
  int usec;     // calculated value to send to servo
  float sf;     // scaling factor mapping -100..100 to lo..hi 

  mythrust = t;

  lo = mycfg->mid - mycfg->span;
  sf = (2.0 * mycfg->span) / 200.0;
  usec = mycfg->reverse * t * sf + lo + mycfg->span;
  myservo.writeMicroseconds(usec);
}
