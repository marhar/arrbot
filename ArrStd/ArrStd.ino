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
