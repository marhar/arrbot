//----------------------------------------------------------------------
// ArrStd.c -- some standard ArrBot utility things
//----------------------------------------------------------------------

extern void countdown(int n = 5)
{
  while (n-- > 0) {
    P("countdown... ");
    PL(n);
    delay(1000);
  }
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
