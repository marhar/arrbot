//----------------------------------------------------------------------
// Show Current Configuration
//----------------------------------------------------------------------

#include <Servo.h> 
#include <EEPROM.h>
#include "/arrbot/arrservos.h"
#include "/arrbot/arrheader.h"

arrbot_cfg cfg;                         // the arrbot configuration

#define P(x)  Serial.print(x)
#define NL() P(F("\r\n"))
#define P3(a,b)  P(F(a)); P(b); P(";"); NL()

//----------------------------------------------------------------------
// show_cfg -- show the configuration data
//----------------------------------------------------------------------

void show_cfg(arrbot_cfg *c)
{
  P("--"); NL();
  P3("magic   = ", c->magic);
  P3("version = ", c->version);
  P3("sz      = ", c->sz);
  P3("cksum   = ", c->cksum);
  P3("  cfg.l.mid     = ", c->l.mid);
  P3("  cfg.l.span    = ", c->l.span);
  P3("  cfg.l.reverse = ", c->l.reverse);
  P3("  cfg.r.mid     = ", c->r.mid);
  P3("  cfg.r.span    = ", c->r.span);
  P3("  cfg.r.reverse = ", c->r.reverse);
  NL();
}

//----------------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  cfg.read();
}

//----------------------------------------------------------------------
void loop() {
  show_cfg(&cfg);
  delay(5000);
}

