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

#endif
