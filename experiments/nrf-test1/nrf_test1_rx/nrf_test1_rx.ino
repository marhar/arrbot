#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

int joystick[5];  // 2 element array holding Joystick readings

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(19200);
  delay(1000);

  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}


#define P(x) Serial.print(x); Serial.print(" ")
void loop()
{
  if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done) {
      done = radio.read( joystick, sizeof(joystick) );
    }
    for (int i = 0; i < 5; ++i) {
      P(joystick[0]);
    }
    Serial.println(""); 
  }
  else
  {    
      Serial.println("No radio available");
  }
}
