/*
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 */
 
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

int led = 13;
int data = 0;

void setup() {                
  pinMode(led, OUTPUT);

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();


}

void loop() {
  
  data += 1;
  Mirf.setTADDR((byte *)"clie1");
  Mirf.send(data);

  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}
