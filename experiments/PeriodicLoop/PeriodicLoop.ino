void ding(int ch)
{
  static int col = 0;
  
  Serial.write(ch);
  if (col++ > 50) {
    col = 0;
    Serial.print("\n");
  }
}

void ten_hz(void)
{
  ding('.');
}

unsigned long loopcount;

void one_hz(void)
{
  ding('1');
  Serial.print("(");
  Serial.print(loopcount);
  Serial.print(")");
  loopcount = 0;
}

void kilo_hz(void)
{
}

void fastest(void)
{
  ++loopcount;
}

void setup() { 

  unsigned long last_1hz_click;
  unsigned long last_10hz_click;
  unsigned long click;
  
  Serial.begin(115200); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  last_10hz_click = last_1hz_click = micros();
  for (;;) {
    click = micros();
    if (click - last_1hz_click > 1000000) {
        one_hz();
        last_1hz_click = click;
    }
    if (click - last_10hz_click > 100000) {
        ten_hz();
        last_10hz_click = click;
    }
    //if (click % 100000 == 0)
    //    ten_hz();
    fastest();
  }
} 


void loop()
{
}
