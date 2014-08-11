#ifndef _ARSERVOS_H
#define _ARSERVOS_H

#include <Servo.h>

struct arrbot_servocfg
{
    int mid;     // midpoint of servo, where it doesn't move the wheel 
    int span;    // how much mid can be {inc,dec}remented for full travel
    int reverse; // is this servo reversed? 1 = no, -1 = yes

    void init();
};

//----------------------------------------------------------------------
// arrbot_servo -- scale and issue servo commands
//----------------------------------------------------------------------
struct arrbot_servo
{
  Servo myservo;           // servo we're controlling
  int   mythrust;          // thrust value for our servo (-100..100)
  arrbot_servocfg* mycfg;  // our servo config

  void thrust(int t);
  void attach(int pin, arrbot_servocfg* pc);
};

#endif
