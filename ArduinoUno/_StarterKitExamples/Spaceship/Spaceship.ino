/*
  Arduino Starter Kit example
  https://store.arduino.cc/genuino-starter-kit
*/

int switchstate = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(2, INPUT);
}

void loop() {
  switchstate = digitalRead(2);

  // if the button is not pressed turn on the green LED and off the red LEDs
  if (switchstate == LOW) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  // if the switch is not LOW (the button is pressed) turn off the green LED and blink alternatively the red LEDs
  else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(250);

    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(250);
  }
}
