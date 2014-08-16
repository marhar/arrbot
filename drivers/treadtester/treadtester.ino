//----------------------------------------------------------------------
// Tread Tester
//
// This simply cycles through a series of tread motions, moving the
// arrbot forwards, backwards, turning in circles, etc.
//
// It's a good test to run for when you attach your servos and
// arduino for the first time.
//
// this version does not read the calibration data.
// left servo is on port 9.
// right servo is on port 10.
//----------------------------------------------------------------------

#include <Servo.h> 
 
//----------------------------------------------------------------------
// Servo customization
// There are two servos, left and right.
// - each servo has a midpoint where it doesn't move
// - ach servo has an offset from the midpoint to the high, low points
// - these offsets are currently the same value unless that proves
//   problematic.
// - we map servo values thus: (-100,0,100) ==> (mid-off,off,mid+off)
//
// note: later this will come from eprom
//----------------------------------------------------------------------

Servo lserv;                // left wheel or tread
Servo rserv;                // right wheel or tread

int lmid = 1500;             // mid value,  where servo is stopped
int loff = 500;              // offset to hi and lo servo values
int lrev = 1;                // -1 to reverse servor or 1 for normal
int lcurr = lmid;            // current value of servo

int rmid = 1500;             // mid value,  where servo is stopped
int roff = 500;              // offset to hi and lo servo values
int rrev = 1;                // -1 to reverse servor or 1 for normal
int rcurr = rmid;            // current value of servo

//----------------------------------------------------------------------
// display -- show the current values
//----------------------------------------------------------------------

#define P Serial.print
#define P2(a, b) P(a); P(b)
void display() {
  P2(" lmid: ", lmid);
  P2(" rmid: ", rmid);
  P2(" lcurr: ", lcurr);
  P2(" rcurr: ", rcurr);
  P("        \r\n");
}

//----------------------------------------------------------------------
// set -- set the left and right servo tread speeds
// -100 = full reverse, 0 = stop, 100 = full forward
//----------------------------------------------------------------------

void set(int lval, int rval)
{
  float ltic = (2.0 * loff) / 200.0;    // tics per percentage value
  float rtic = (2.0 * roff) / 200.0;

  int nl = lmid + lval * ltic * lrev;  // new values for left, right
  int nr = rmid + rval * rtic * rrev;

  P2(" ltic: ", ltic);
  P2(" rtic: ", rtic);
  P2(" XXX lval: ", lval);
  P2(" rval: ", rval);
  P2(" XXX nl: ", nl);
  P2(" nr: ", nr);

  
  // if the value has changed, write it
  if (nl != lcurr) {
    lcurr = nl;
    lserv.writeMicroseconds(rcurr);
  }
  
  if (nr != rcurr) {
    rcurr = nr;
    rserv.writeMicroseconds(rcurr);
  }
  display();
}

//----------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  lserv.attach(9);
  rserv.attach(10);
}

struct pair {
  int a;
  int b;
};

struct pair tests[] = {
  {0, 0},
  {100, 100},
  {-100, -100},
  {0, 100},
  {100, 0},
  {0, -100},
  {-100, 0},
  {100, 50},
  {-100, -50},
  {50, 100},
  {-50, -100},
};

//----------------------------------------------------------------------
void loop() {
  
  int d = 1000;   // duration for each step
  int i;
  
  P("--- hi\n");
  for (i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
    set(tests[i].a, tests[i].b);
    delay(d);
  }
  
  // half speed
  P("--- half\n");
  for (i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
    set(tests[i].a/2, tests[i].b/2);
    delay(d);
  }
}
