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
 
Servo lserv;                // left wheel or tread
Servo rserv;                // right wheel or tread

int lhi = 2000;              // high value, where servo is fastest CCW
int lmid = 1500;             // mid value,  where servo is stopped
int llo = 1000;              // low value,  where servo is fastest CW
int lrev = 1;                // -1 to reverse servor or 1 for normal
int lcurr = lmid;            // current value of servo

int rhi = 2000;              // high value, where servo is fastest CCW
int rmid = 1500;             // mid value,  where servo is stopped
int rlo = 1000;              // low value,  where servo is fastest CW
int rrev = 1;                // -1 to reverse servor or 1 for normal
int rcurr = rmid;            // current value of servo

//----------------------------------------------------------------------
// display -- show the current values
//----------------------------------------------------------------------

#define P Serial.print
#define P2(a, b) P(a); P(b)
void display() {
  P2("lmid: ", lmid);
  P2(" rmid: ", rmid);
  P2(" lcurr: ", lcurr);
  P2(" rcurr: ", rcurr);
  P("        \r");
}

//----------------------------------------------------------------------
// set -- set the left and right servo tread speeds
// -100 = full reverse, 0 = stop, 100 = full forward
//----------------------------------------------------------------------

void set(int lval, int rval)
{
  int nl, nr;        // new values for left, right servos


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
  Serial.begin(115200);
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
  {-100, -100};
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
  
  for (i = 0; i < sizof(tests) / sizeof(tests[0]); ++i) {
    set(tests[i].a, tests[i].b);
    delay(d);
  }
  
  // half speed
  for (i = 0; i < sizof(tests) / sizeof(tests[0]); ++i) {
    set(tests[i].a/2, tests[i].b/2);
    delay(d);
  }
}
