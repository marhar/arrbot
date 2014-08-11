#ifndef _ARHEADER_H
#define _ARHEADER_H

#include <Arduino.h>
#include <EEPROM.h>
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
