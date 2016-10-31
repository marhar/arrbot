// -- set the battery mAh on Giles resistance meter
// The Giles resistance meter sets the capacity of the battery in
// order to calculate the battery's correct C rating.
//
// This is done with the following sequence:
//   long-press; one short press for each 100's digit;
//   long-press; one short press for each 1000's digit;
//   long-press.
//
//   So, to set a 2500 mAh battery, the sequence would be
//   long short short short short short long short short long.
//
// That's a bit tedious, hence this program which does the
// pressing for you.
//
// The intention is to use an LCD to display the values, but for
// now we'll use the serial monitor.

#define RELAY 7

// send a pulse, aka depress and hold the button
void pulse(int d)
{
  digitalWrite(RELAY, HIGH);
  delay(d);
  digitalWrite(RELAY, LOW);
  delay(300);
}

// short pulse
void shortp() {
  pulse(300);
}

// long pulse
void longp() {
  pulse(1000);
}

int vals[] = { 500, 800, 850, 1000, 1500, 1800, 2200, 3000, 4000, 5000 };
int nvals = sizeof(vals)/sizeof(vals[0]);
int curr = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
}

// initiate the pulse sequence
void go(int x) {
  int i;
  Serial.print("go ");

  x = x / 100;  
  Serial.print(" ");
  Serial.print(x);

  int d0 = x % 10;
  int d1 = x / 10;
  Serial.print(" ");
  Serial.print(d0);
  Serial.print(" ");
  Serial.print(d1);
  
  Serial.println("");

  longp();
  for (i = 0; i < d0; ++i)
    shortp();
  longp();
  for (i = 0; i < d1; ++i)
    shortp();
  longp();
}

void loop() {
    int ch;
    if (Serial.available() > 0) {
      ch = Serial.read();
      if (ch == 'j') {
        curr = (curr + 1) % nvals;
      }
      else if (ch == 'k') {
        curr -= 1;
        if (curr < 0) {
          curr = nvals - 1;
        }
      }
      else if (ch == 'g') {
        go(vals[curr]);
      }
      Serial.println(vals[curr]);
    }
}
