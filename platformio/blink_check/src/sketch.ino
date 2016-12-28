// initial programming/blink test for the rfcrafting board

#define BUILT_IN_LED 9

void setup() {
  pinMode(BUILT_IN_LED, OUTPUT);
}

void loop() {
  digitalWrite(BUILT_IN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(BUILT_IN_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
