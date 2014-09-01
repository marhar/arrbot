// Get values from nunchuk, send out via nrf radio transmitter.
// This combines ArrBot_NunchukTest with ideas from nrf_test1_tx.
// By Kurt 8/14/14 

// ArrNunchuck depends on Wire.h
#include <Wire.h>a
#include <ArrNunchuck.h>


// send a packet at 10 Hz,
//
//  - CONNECTIONS: nRF24L01 Modules See:
//http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
//   1 - GND
//   2 - VCC 3.3V !!! NOT 5V
//   3 - CE to Arduino pin 9
//   4 - CSN to Arduino pin 10
//   5 - SCK to Arduino pin 13
//   6 - MOSI to Arduino pin 11
//   7 - MISO to Arduino pin 12
//   8 - UNUSED
//

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

ArrNunchuck nunchuk = ArrNunchuck();


int joystick[5];  //  array holding Joystick readings


void
setup() {
//  delay(2000);
  Serial.begin(9600);
  Serial.println("Start setup.");
//  delay(10000);
  nunchuk.init();
  Serial.println("Nunchuk initialized.");
  
  // Setup pins / SPI.
  Mirf.cePin = 9;
  Mirf.csnPin = 10;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  // Configure reciving address.
  Mirf.setRADDR((byte *)"clie1");
  
  // Set the payload length. Payload on client and server must be the same!!!!
   Mirf.payload = 5 * sizeof(int);
   
  // Write channel and payload config then power up reciver.
  // NB: Make sure channel is legal in your area.
  Mirf.channel = 18*3;

  Mirf.config();
  Mirf.setTADDR((byte *)"serv1");

  Serial.println("Mirf initialized.");
}

unsigned long last;  // last time

void
loop() {
  nunchuk.update();
  
  int now = millis();
  unsigned long time = millis();
  Serial.print( now - last );  // print elapsed ms
  last = now;
  
  Serial.print("ms\t(");
  Serial.print(nunchuk.stickX);
  Serial.print(", ");
  Serial.print(nunchuk.stickY);
#if 0
  Serial.print(")\taccel:");
  Serial.print("(");
  Serial.print(nunchuk.accelX);
  Serial.print(", ");
  Serial.print(nunchuk.accelY);
  Serial.print(", ");
  Serial.print(nunchuk.accelZ);
#endif
  Serial.print(")\t buttons");
  Serial.print(nunchuk.buttonC);
  Serial.print(nunchuk.buttonZ);
  Serial.println("");

  joystick[0] = nunchuk.stickX;
  joystick[1] = nunchuk.stickY;
  joystick[2] = nunchuk.buttonC;
  joystick[3] = nunchuk.buttonZ;
  joystick[4] = now;

//   Mirf.setTADDR((byte *)"serv1");
  Mirf.send((byte *)&joystick);
  Serial.print("Send: ");
  Serial.print(joystick[0]);
  Serial.print(" ");
  Serial.println(joystick[1]);
  while(Mirf.isSending()){
      delay(5);
  }
  Serial.println("Finished sending");

  // reduce this delay once things are debugged.
  delay(50);
  
#if 0
  // Later, may want to implement acknowledgement.
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
  
  unsigned long recv;
  Mirf.getData((byte *) &recv);
  
  Serial.print("  Ack: ");
  Serial.println(recv);
#endif
   delay(10);
}




