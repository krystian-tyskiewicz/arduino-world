#include <Ultrasonic.h>

const int TRIG = 9;
const int ECHO = 10;
const int BUZZER_PIN = 8;

const int MAX_RANGE = 200;

Ultrasonic ultrasonic(TRIG, ECHO);

void setup() {
  Serial.begin(9600);
}

void loop() {
  long distance = ultrasonic.read();
  Serial.println(distance);

  if (distance > 0 && distance < MAX_RANGE) {
    tone(BUZZER_PIN, 440, 200);
  }

  delay(500);
}
