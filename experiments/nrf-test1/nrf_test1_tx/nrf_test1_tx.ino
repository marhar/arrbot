// nrf_test1_tx
//
// send a packet at 10 Hz, putting some incrementing values
// in that packet.
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

#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
int joystick[5];  // 2 element array holding Joystick readings

int led = 13;

void setup()
{
  pinMode(led, OUTPUT);     
  radio.begin();
  radio.openWritingPipe(pipe);
}

int x;

void loop()
{
  joystick[0] = ++x;
  joystick[1] = ++x;
  joystick[2] = ++x;
  joystick[3] = ++x;
  joystick[4] = ++x;

  digitalWrite(led, HIGH);
  delay(10);

  radio.write(joystick, sizeof(joystick));
  digitalWrite(led, LOW);
  delay(100);
}
