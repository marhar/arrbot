//----------------------------------------------------------------------
// Servo Calibrator
//
// You want to find the midpoint and span of your continuous
// rotation servos.
//
//  mid  = value where servo is stopped
//  span = offset for maximum servo travel.  [mid-span..mid+span]
//
// upload this sketch, and then run either
//
// mac:      screen /dev/tty.usbmodem1421 115200
// windows:  putty com8 115200
//
//     (use serial port specified in Arduino menu tools/Serial port)
//     (quit screen with: ctrl-A ctrl-\)
//
// commands:
//
//   1 -- left servo
//   2 -- right servo
//
//   a -- subtract 1 from mid
//   s -- add      1 to   mid
//   d -- subtract 1 from span
//   f -- add      1 to   span
//   g -- reverse
//
//   r -- read cfg
//   w -- write cfg
//   i -- initialize cfg to defaults
//
//   , -- jump to lo position
//   . -- jump to mid
//   / -- jump to hi
//
//----------------------------------------------------------------------

#include <Servo.h> 
#include <EEPROM.h>
#include "ArrServos.h"
#include "ArrHeader.h"

arrbot_cfg cfg;

Servo lserv;       // left servo
Servo rserv;       // right servo
Servo *cserv;      // current servo

#define P(x) Serial.print(x)
#define P2(a, b) P(a); P(b)
#define PV(x) P(x); P(" ");
//#define PV(x) P(" " #x ": "); P(x);

char spinners[] = "|/-\\";  // eye candy: shows pgm is running
int  spinnerc=0;            // counter for eye candy


//----------------------------------------------------------------------
// display -- display the current state of things
//----------------------------------------------------------------------

char *m1, *m2, *m3;
void display() {
  PV(cfg.magic);
  PV(cfg.version);
  PV(cfg.sz);
  PV(cfg.cksum);
  P(m1);
  PV(cfg.l.mid);
  PV(cfg.l.span);
  PV(cfg.l.reverse);
  P(m2);
  PV(cfg.r.mid);
  PV(cfg.r.span);
  PV(cfg.r.reverse);
  P(m3);
  P(spinners[spinnerc++%4]);
  P("\r");
}

int lcurr;    // left servo current value
int rcurr;    // right servo current value


//----------------------------------------------------------------------
// actleft -- set left servo active
//----------------------------------------------------------------------
void actleft()
{
  cserv = &lserv;
  m1="<";m2="> ";m3=" ";
}

//----------------------------------------------------------------------
// actright -- set right servo active
//----------------------------------------------------------------------
void actright()
{
  cserv = &rserv;
  m1=" ";m2=" <";m3=">";
}

//----------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  lserv.attach(9);
  rserv.attach(10);
  cfg.init();
  lcurr = cfg.l.mid;
  rcurr = cfg.r.mid;
  actleft();
}

#define MNS 1000    // minimum allowed servo value
#define MXS 2000    // maximum allowed servo value

//----------------------------------------------------------------------
void loop() {
  
  int cmd;
  if (Serial.available() > 0) {
    cmd = Serial.read();
    Serial.read();
  }
  
  switch (cmd) {
    case '1': actleft();                             break; // left active
    case '2': actright();                            break; // right active
    case 'i': cfg.init();                            break; // sane initialize
    case 'w': cfg.write();                           break; // write cfg to eeprom
    case 'r': cfg.read();                            break; // read cfg from eeprom
    case 'a': if (cfg. NEED CURR z->mid - z->span > MNS) z->mid--;  break;
    case 's': if (z->mid + z->span < MXS) z->mid++;  break;
    case 'd': if (z->mid - z->span > MNS) z->span--; break;
    case 'f': if (z->mid + z->span < MXS) z->span++; break;
    case 'g': z->reverse = -z->reverse;              break;
    


/*
    case 'a': curr = lo; break;
    case 's': curr = mid; break;
    case 'd': curr = hi; break;
    case 'A': lo  = curr; break;
    case 'S': mid = curr; break;
    case 'D': hi  = curr; break;
    case 'j': curr -= 1; break;
    case 'k': curr += 1; break;
    case 'J': curr -= 10; break;
    case 'K': curr += 10; break;
*/
  }
  
  display();
  lserv.writeMicroseconds(lcurr);
  rserv.writeMicroseconds(rcurr);
  delay(20);
}
