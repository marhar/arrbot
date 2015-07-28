#ifndef _ARRMOTEHEADER_H
#define _ARRMOTEHEADER_H

#include <Arduino.h>
#include <EEPROM.h>

// hertz
// beacon
// add status led
// two way telemetry

#define ARRMOTE_MAGIC 0x7262  // magic number for this header ("as")
#define ARRMOTE_HVERSION 1    // version number of this header
struct arrmote_cfg
{
    unsigned int magic;    // magic number, is this good data?
    unsigned int version;  // version of this config header
    unsigned int sz;       // size of this header
    unsigned int cksum;    // checksum of data following checksum

    unsigned int device;

    // for this radio
    unsigned int channel;
    // calibration data
    // speed
    
    void read();           // read header from eprom
    void write();          // write header to eprom
    void init();           // init header with proper values

};
#endif
