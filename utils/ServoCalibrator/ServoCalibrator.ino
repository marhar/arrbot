//----------------------------------------------------------------------
// Servo Calibrator
//
// You want to find the low, high, and midpoints of your continuous
// rotation servo.
//
//  low  = value where servo spins the fastest clockwise
//  high = value where servo spins the fastest counter clockwise
//  mid  = value where servo is stopped
//
//
// upload this sketch, and then run either
//
// mac:      screen /dev/tty.usbmodem1421 115200
// windows:  putty com8 115200
//
//     (use serial port specified in Arduino menu tools/Serial port)
//     (quit screen with: ctrl-A ctrl-\)
//
// most important commands:
//   j -- subtract one from position
//   k -- add one to position
//
//   A -- set low position from current position
//   S -- ditto mid
//   D -- ditto high
//
//   a -- jump to low position
//   s -- ditto mid
//   d -- ditto high
//
//----------------------------------------------------------------------

#include <Servo.h> 
 
Servo serv;                 // servo object
char spinners[] = "|/-\\";  // eye candy: shows pgm is running

int count=0;                // counter for eye candy

int hi = 2000;              // high value, where servo is fastest CCW
int mid = 1500;             // mid value,  where servo is stopped
int lo = 1000;              // low value,  where servo is fastest CW
int curr = mid;

//----------------------------------------------------------------------
// display -- show the current values
//----------------------------------------------------------------------

void display() {
  Serial.print("lo: "); Serial.print(lo);
  Serial.print(" mid: "); Serial.print(mid);
  Serial.print(" hi: "); Serial.print(hi);
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
  
  int cmd;
  if (Serial.available() > 0) {
    cmd = Serial.read();
    Serial.read();
  }
  
  switch (cmd) {
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
  }
  
  display();
  serv.writeMicroseconds(curr);
  delay(100);
}
