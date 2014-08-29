//----------------------------------------------------------------------
// 8/16/14 -  First light using Mirf radio control for arrbot
//  Kurt Fleischer
//
// Modified from ServoTester and Mirf/ping_server
//
// 8/21/14 Added fail counter, and halt servos if 
//   communication is flakey.
//----------------------------------------------------------------------


/**
* An Mirf receiver for nunchuk commands.
*
* Pins:
* Hardware SPI:
* MISO -> 12
* MOSI -> 11
* SCK -> 13
*
* Configurable:
* CE -> 9
* CSN -> 10
*
*/

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>


// Stuff for the servos
#include <Servo.h> 

#define LBK 1050    // lowest servo value we can safely set
#define LHALT 1377  // servo value to hold still
#define LFWD  1700    // highest servo value we can safely set
#define RBK 1650    // lowest servo value we can safely set
#define RHALT 1369  // servo value to hold still
#define RFWD  1050    // highest servo value we can safely set


//----------------------------------------------------------------------
// globals
//----------------------------------------------------------------------

Servo lserv;                 // left wheel servo object
Servo rserv;                 // right wheel servo object

int left = LHALT;
int right = RHALT;

//----------------------------------------------------------------------
void setup() {

  Serial.begin(9600);
  Serial.println("in da beginning...");

  left = LHALT; right = RHALT;         // halt

  // Setup pins / SPI.
  Mirf.spi = &MirfHardwareSpi;
  Mirf.cePin = 9;
  Mirf.csnPin = 10;
  Mirf.init();

  // Configure receiving address.
  Mirf.setRADDR((byte *)"serv1");

 /* Set the payload length to sizeof(unsigned long) the
  * return type of millis().
  *
  * NB: payload on client and server must be the same.
  */
  Mirf.payload = 5 * sizeof(int);

 // Write channel and payload config then power up reciver.
 Mirf.config();

#define SERVO 1
#if SERVO
  // See "BUG" note above.
  lserv.attach(7);
  rserv.attach(8);
#endif

#if SERVO
  Serial.println("Halting");
  // Once RF bugs are worked out, we want to do this to start off halted.
  lserv.writeMicroseconds(left);
  rserv.writeMicroseconds(right);
#endif
  Serial.println("Listening..."); 
}

int nsuccess = 0;
int nfail = 0;
int failSinceLastSuccess = 0;

//----------------------------------------------------------------------
void loop() 
{
 int oldleft = left;
 int oldright = right;
 int joystick[5];

 // does this help to have it here? Not sure.
//   Mirf.setRADDR((byte *)"serv1");

 // if signal is lost for too long, we halt:
 if ( failSinceLastSuccess > 10) {
     left = LHALT; right = RHALT;
 }

  // If a packet has been received.
 int delayt = 35;
 if(!Mirf.isSending() && Mirf.dataReady()){
    failSinceLastSuccess = 0;

    // load the packet into the buffer.
     Mirf.getData( (byte *) joystick);

     delay(delayt);
     Serial.print("= ");
     for (int i=0; i<5; i++) {
       Serial.print(joystick[i]);
       Serial.print(" ");
     }

     // CRUDE MAPPING from joystick to servos.
     if (joystick[0] < 30) {
       Serial.println("TURN LEFT");
         left = LBK; right = RFWD;     // left
        // try to keep left tread from coming off
         left = (3*LHALT + LBK)/4;
     }
     else if (joystick[0] > 200) {
       Serial.println(">>right>>");
       left = LFWD; right = RBK;     // right
        // try to keep right tread from coming off
        right = (3*RHALT + RBK)/4;
     }
     else if (joystick[1] < 50) {
        left = LBK; right = RBK;   // reverse
     }
     else if (joystick[1] > 200) {
       left = LFWD; right = RFWD;
     }
     else {
         left = LHALT; right = RHALT;
     }
     Serial.print("\tl ");
     Serial.print(left);
     Serial.print(",\tr ");
     Serial.println(right);
     nsuccess++;
     Serial.print("Success: ");      
     Serial.print(nsuccess);
     Serial.print(", Fail: ");
     Serial.println(nfail);
 }
 else {
   failSinceLastSuccess++;
   nfail++;
   if ( (nfail % 10) == 0) {
       Serial.print("Fail: ");
       Serial.print(nfail);
       Serial.print(", success: ");
       Serial.println(nsuccess);
   }
//    delay(delayt);
 }
#if SERVO
  // See "BUG" note above.
  if (oldleft != left) {
    Serial.println("  Set left");
    lserv.writeMicroseconds(left);
  }
#endif


#if SERVO
  if (oldright != right) {
    Serial.println("  Set right");
    rserv.writeMicroseconds(right);
  }
#endif
  delay(20);

}
