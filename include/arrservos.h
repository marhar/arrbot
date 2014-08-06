#ifndef _ARSERVOS_H
#define _ARSERVOS_H
struct arrbot_servocfg
{
    int mid;     // midpoint of servo, where it doesn't move the wheel 
    int span;    // how much mid can be {inc,dec}remented for full travel
    int reverse; // is this servo reversed? 1 = no, -1 = yes

    void init();
};

//----------------------------------------------------------------------
// init -- initialize with some reasonable values (1000/1500/2000)
//----------------------------------------------------------------------

void arrbot_servocfg::init() {
  this->mid = 1500;
  this->span = 500;
  this->reverse = 1;
}

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
  usec = t * sf + lo + mycfg->span;
  myservo.writeMicroseconds(usec);
}

#endif
