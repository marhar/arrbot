#ifndef _ARHEADER_H
#define _ARHEADER_H

#include <Arduino.h>
#include "ArrServos.h"


#define ARRBOT_MAGIC 0x7261  // magic number for this header ("ar")
#define ARRBOT_HVERSION 1    // version number of this header
struct arrbot_cfg
{
    unsigned int magic;    // magic number, is this good data?
    unsigned int version;  // version of this config header
    unsigned int sz;       // size of this header
    unsigned int cksum;    // checksum of data following checksum
    arrbot_servocfg l;     // left servo
    arrbot_servocfg r;     // right servo
    
    void read();           // read header from eprom
    void write();          // write header to eprom
    void init();           // init header with proper values

};
#endif

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
