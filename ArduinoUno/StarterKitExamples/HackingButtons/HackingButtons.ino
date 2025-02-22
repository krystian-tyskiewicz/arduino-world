/*
  Arduino Starter Kit example
  https://store.arduino.cc/genuino-starter-kit
*/

const int optoPin = 2;

void setup() {
  pinMode(optoPin, OUTPUT);
}

void loop() {
  digitalWrite(optoPin, HIGH);

  delay(15);
}
