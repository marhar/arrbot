#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

char *spinner(void)
{
  static char spinch[] = {'/','-','\\','|'};
  static int spincnt = 0;
  static char spinstr[2];

  spinstr[0] = spinch[++spincnt%4];
  spinstr[1] = 0;
  return spinstr;
}

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

int joystick[5];  // 2 element array holding Joystick readings

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  for (int i = 3; i > 0; --i) {
    Serial.print("starting in "); Serial.println(i);
    delay(1000);
  }

  radio.begin();
  radio.setPayloadSize(sizeof(joystick));
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
    Serial.println("");
    for (int i = 0; i < 5; ++i) {
      P(joystick[0]);
    }
    Serial.println(""); 
  }
  else
  {    
      //Serial.print("No radio available");
      //Serial.print(spinner());
      //Serial.print("\r");
  }
}
