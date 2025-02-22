#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;
const int temperatureUpperThreshold = 26;
const int temperatureLowerThreshold = 22;

const int redLEDPin = 9;
const int greenLEDPin = 6;
const int blueLEDPin = 7;

void setup() {
  lcd.begin(16, 2);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = voltage * 100;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print("Min: ");
  lcd.print(temperatureLowerThreshold);
  lcd.print(" Max: ");
  lcd.print(temperatureUpperThreshold);

  if (temperature > temperatureUpperThreshold) {
    tone(8, 440, 200);

    analogWrite(redLEDPin, 255);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
  } else if (temperature < temperatureLowerThreshold) {
    tone(8, 880, 200);

    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 255);
  } else {
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
  }

  delay(2000);
}
