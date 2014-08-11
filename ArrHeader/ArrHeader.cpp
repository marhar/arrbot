#include "ArrHeader.h"

//----------------------------------------------------------------------
void arrbot_cfg::read()
{
  unsigned int i;
  unsigned char *p = (unsigned char*)this;

  for (i = 0; i < sizeof(*this); ++i)
    p[i] = EEPROM.read(i);
}

//----------------------------------------------------------------------
void arrbot_cfg::write()
{
  unsigned int i;
  unsigned char *p = (unsigned char*)this;

  sz = sizeof(*this);
  // TODO: figure out checksum
  cksum = 0;

  // TODO: only write modified bytes
  // TODO: look at EEPROMex lib
  for (i = 0; i < sizeof(*this); ++i)
    EEPROM.write(i, p[i]);

  // TODO: verify data which has been read
}

//----------------------------------------------------------------------
void arrbot_cfg::init()
{
  this->magic = ARRBOT_MAGIC;
  this->version = ARRBOT_HVERSION;
  this->sz = sizeof(*this);
  this->cksum = 0;  // TODO: put chksum here
  this->l.init();
  this->r.init();
}
