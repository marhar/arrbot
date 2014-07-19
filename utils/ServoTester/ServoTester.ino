//----------------------------------------------------------------------
// ServoTester -- test your servos
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
//   c -- center at 1500
//   j -- subtract one from position
//   k -- add one to position
//   J -- subtract ten from position
//   K -- add ten to position
//
//----------------------------------------------------------------------

#include <Servo.h> 

#define LO 1000    // lowest servo value we can safely set
#define HI 2000    // highest servo value we can safely set

#define UP 1       // sweeping up
#define DN 0       // sweeping down

#define SWEEP_STEP 10 // sweep step increment

//----------------------------------------------------------------------
// globals
//----------------------------------------------------------------------
 
Servo serv;                 // servo object
char spinners[] = "|/-\\";  // eye candy: shows pgm is running
int count=0;                // counter for eye candy

int sweeping = 1;           // are we in sweep mode?
int dir = DN;               // direction of sweep
int curr = (LO + HI)/2;     // current position

//----------------------------------------------------------------------
// display -- show the current values
//----------------------------------------------------------------------

void display() {
  Serial.print("sweeping: "); Serial.print(sweeping);
  Serial.print(" curr: "); Serial.print(curr);
  Serial.print(" "); Serial.print(spinners[count++ % sizeof(spinners)]);
  Serial.print("                 \r");
}

//----------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  serv.attach(9);
}

//----------------------------------------------------------------------
void loop() {
  
  int cmd;             // keystroke command from user
  int oldcurr = curr;
  
  if (Serial.available() > 0) {
    cmd = Serial.read();
    Serial.read();
  
    switch (cmd) {
      case 'v': sweeping = 1;                   break;
      case 'j': sweeping = 0; curr -= 1;        break;
      case 'k': sweeping = 0; curr += 1;        break;
      case 'J': sweeping = 0; curr -= 10;       break;
      case 'K': sweeping = 0; curr += 10;       break;
      case 'h': sweeping = 0; curr = HI;        break;
      case 'l': sweeping = 0; curr = LO;        break;
      case 'c': sweeping = 0; curr = (HI+LO)/2; break;
    }
  }
  
  display();
  if (sweeping) {
    if (dir == DN) {
      curr -= SWEEP_STEP;
      if (curr < LO) {
        curr = LO;
        dir = UP;
      }
    }
    else {
      curr += SWEEP_STEP;
      if (curr > HI) {
        curr = HI;
        dir = DN;
      }
    }
  }
  else {
    // not sweeping, just ensure LO <= curr <= HI
    if (curr < LO)
      curr = LO;
    else if (curr > HI)
      curr = HI;
  }
  
  if (oldcurr != curr)
    serv.writeMicroseconds(curr);
  delay(10);
}
