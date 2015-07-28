//----------------------------------------------------------------------
// ArrStd.h -- some standard ArrBot utility things
//----------------------------------------------------------------------

#ifndef ARRBOT_BAUD
//#define ARRBOT_BAUD 9600
#define ARRBOT_BAUD 115200
#endif

//----------------------------------------------------------------------
// some convenient printing macros
//----------------------------------------------------------------------

#define P(x) Serial.print(x)          // print
#define NL(x) Serial.println(x)       // print line
#define PS(x) P(x); P(" ")            // print with space
#define PV(x) P(" " #x ": "); P(x);   // print a variable

//----------------------------------------------------------------------
// declarations for some handy things
//----------------------------------------------------------------------

extern void countdown(int n);
float mapf(float x, float in_min, float in_max, float out_min, float out_max);
