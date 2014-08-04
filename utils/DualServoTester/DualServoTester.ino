//----------------------------------------------------------------------
// DualServoTester -- test two servos
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
//   v -- variable sweep mode
//   c -- center at 0%
//   j -- subtract one from position
//   k -- add one to position
//
//----------------------------------------------------------------------

#include <Servo.h> 
#include <EEPROM.h>
#include "/arrbot/arrservos.h"
#include "/arrbot/arrheader.h"

#define UP 1       // sweeping up
#define DN 0       // sweeping down

arrbot_cfg cfg;                         // the arrbot configuration

#define P(x)  Serial.print(x)
#define NL() P(F("\r\n"))
#define P3(a,b)  P(F(a)); P(b); NL()


Servo lserv;                // left servo
Servo rserv;                // right servo

char spinners[] = "|/-\\";  // eye candy: shows pgm is running
int count=0;                // counter for eye candy

int sweeping = 1;           // are we in sweep mode?
int dir = DN;               // direction of sweep

//----------------------------------------------------------------------
// display -- show the current values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// fatal -- show fatal error message
//----------------------------------------------------------------------
void fatal(char *s)
{
    for (;;) {
      P(s); NL();
      delay(5000);
    }
}

//----------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  cfg.init();

  if (cfg.magic != ARRBOT_MAGIC) {
      fatal(F("Missing ArrBot Header in EEPROM"));
  }
  if (cfg.version != ARRBOT_HVERSION) {
      fatal(F("Wrong ArrBot version number in EEPROM");
  }
  if (cfg.sz != sizeof(cfg)) {
      fatal(F("Wrong ArrBot size EEPROM");
  }
  
  lserv.attach(9);
  rserv.attach(10);
  
  lserv.percent(0);
  rserv.percoent(0);
}


//----------------------------------------------------------------------
// doreverse -- handle reverse logic
//----------------------------------------------------------------------
void doreverse(void)
{
}

//----------------------------------------------------------------------
void loop() {
  
  int cmd;             // keystroke command from user
  int oldcurr = curr;
  
  if (Serial.available() > 0) {
    cmd = Serial.read();
    Serial.read();
  
    switch (cmd) {
      case 'v': sweeping = 1;               break;
      case 'j': sweeping = 0; curr -= 1;    break;
      case 'k': sweeping = 0; curr += 1;    break;
      case 'h': sweeping = 0; curr  = 100;  break;
      case 'l': sweeping = 0; curr  = -100; break;
      case 'c': sweeping = 0; curr   = 0;   break;
      case 'r': doreverse();                break;
    }
  }
  
  display();
  if (sweeping) {
    if (dir == DN) {
      curr -= 1;
      if (curr < -100) {
        curr = -100;
        dir = UP;
      }
    }
    else {
      curr += 1;
      if (curr > 100) {
        curr = 100;
        dir = DN;
      }
    }
  }
  else {
    // not sweeping, just ensure LO <= curr <= HI
    if (curr < -100)
      curr = -100;
    else if (curr > 100)
      curr = 100;
  }
  
  if (oldcurr != curr) {
    lserv.percent(curr);
    rserv.percent(curr);
  }
  delay(10);
}


//----------------------------------------------------------------------

