//----------------------------------------------------------------------
// Basic Servo Calibrator
//
// Set the mid and span values for both servos in setup().
// These values will be written to the arrbot eprom.
//----------------------------------------------------------------------

#include <Servo.h> 
#include <EEPROM.h>
#include "/arrbot/arrservos.h"
#include "/arrbot/arrheader.h"

arrbot_cfg cfg;                         // the arrbot configuration

#define P(x)  Serial.print(x)
#define NL() P(F("\r\n"))
#define P3(a,b)  P(F(a)); P(b); NL()

//----------------------------------------------------------------------
// show_cfg -- show the configuration data
//----------------------------------------------------------------------

void show_cfg(arrbot_cfg *c)
{
  P3("magic   = ", c->magic);
  P3("version = ", c->version);
  P3("sz      = ", c->sz);
  P3("cksum   = ", c->cksum);
  P(F("left:")); NL();
  P3("  mid     = ", c->l.mid);
  P3("  span    = ", c->l.span);
  P3("  reverse = ", c->l.reverse);
  P(F("right:")); NL();
  P3("  mid     = ", c->r.mid);
  P3("  span    = ", c->r.span);
  P3("  reverse = ", c->r.reverse);
  NL();
}

//----------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);

  for (int i = 8; i > 0; --i) {
    P("initializing in "); P(i); NL();
    delay(1000);
  }
  
  P("initializing configuration..."); NL();
  cfg.init();

  // CHANGE THESE VALUES FOR YOUR PARTICULAR SERVOS

  cfg.l.mid = 1500;
  cfg.l.span = 500;
  cfg.l.reverse = 1;
  
  cfg.r.mid = 1500;
  cfg.r.span = 500;
  cfg.l.reverse = 1;

  P("setting configuration:"); NL(); NL();
  show_cfg(&cfg);
  
  P("writing configuration..."); NL();
  cfg.write();
  
  P("reading configuration..."); NL();
  cfg.init();
  cfg.read();
  NL();

  P("Stored configuration is:\n\n");
  show_cfg(&cfg);
  
  P("finished!"); NL();
}

//----------------------------------------------------------------------
void loop() {
  delay(10000);  
}
