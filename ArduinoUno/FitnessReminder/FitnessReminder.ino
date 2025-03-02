#include <LiquidCrystal.h>

#define HIGHLIGHT_PIN 10
#define BUZZER_PIN 3

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

struct Exercise {
  const char* name;
  const char* repetitions;
};

Exercise exercises[] = {
  { "Pompki", "15x" },
  { "Brzuszki", "20x" },
  { "Przysiady", "20x" },
  { "Plank", "60s" },
  { "Hantle biceps", "12x" },
  { "Hantle triceps", "12x" },
  { "Martwy ciag", "10x" },
  { "Burpees", "15x" },
  { "Przysiady z hantlami", "12x" },
  { "Mountain Climbers", "30s" },
  { "Podskoki", "30s" },
  { "Rozciaganie karku", "Brak" },
  { "Pajacyki", "30s" },
  { "Przyciaganie kolan", "20x" },
  { "Rozciaganie barkow", "Brak" },
  { "Skłony boczne", "20x" },
  { "Spacer farmera", "30s" },
  { "Rotacja barkow", "15x" },
  { "Rozgrzewka nadgarstkow", "Brak" },
  { "Deska bokiem", "30s" },
  { "Wykroki", "12x" },
  { "Unoszenie nog", "15x" },
  { "Przysiady z wyskokiem", "15x" },
  { "Unoszenie boczne hantli", "12x" },
  { "Bieganie w miejscu", "60s" },
};

int currentExercise = 0;

enum Button { NONE, SELECT, LEFT, UP, DOWN, RIGHT };
Button previousPressedButton = NONE;

unsigned long lastReminder = 0;
const unsigned long interval = 1000UL * 60 * 10;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(HIGHLIGHT_PIN, OUTPUT);
  randomSeed(analogRead(A1));

  displayCurrentExercise();
  turnOnBacklight();
}

void loop() {
  const Button pressedButton = getPressedButton(analogRead(A0));

  if (pressedButton != previousPressedButton) {
    handleButtonAction(pressedButton);
  }

  if (millis() - lastReminder >= interval) {
    pickRandomExercise();
  }

  previousPressedButton = pressedButton;

  delay(100);
}

Button getPressedButton(int buttonValue) {
  if (buttonValue > 900) {
    return NONE;
  } else if (buttonValue > 750) {
    return SELECT;
  } else if (buttonValue > 500) {
    return LEFT;
  } else if (buttonValue > 300) {
    return DOWN;
  } else if (buttonValue > 100) {
    return UP;
  } else {
    return RIGHT;
  }
}

void handleButtonAction(Button button) {
  if (button == DOWN || button == LEFT) {
    setPrevExercise();
  } else if (button == UP || button == RIGHT) {
    setNextExercise();
  } else if (button == SELECT) {
    markAsDone();
  }
}

void pickRandomExercise() {
  const int numberOfExercises = getNumberOfExercises();
  currentExercise = random(0, numberOfExercises);
  displayCurrentExercise();
  turnOnBacklight();
  resetTimer();
  playSound();
}

void setNextExercise() {
  const int numberOfExercises = getNumberOfExercises();
  if (currentExercise + 1 == numberOfExercises) {
    currentExercise = 0;
  } else {
    currentExercise++;
  }
  displayCurrentExercise();
  turnOnBacklight();
  resetTimer();
}

void setPrevExercise() {
  const int numberOfExercises = getNumberOfExercises();
  if (currentExercise - 1 < 0) {
    currentExercise = numberOfExercises - 1;
  } else {
    currentExercise--;
  }
  displayCurrentExercise();
  turnOnBacklight();
  resetTimer();
}

void displayCurrentExercise() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(exercises[currentExercise].name);
  lcd.setCursor(0, 1);
  lcd.print(exercises[currentExercise].repetitions);
}

int getNumberOfExercises() {
  return sizeof(exercises) / sizeof(exercises[0]);
}

void resetTimer() {
  lastReminder = millis();
}

void markAsDone() {
  turnOffBacklight();
}

void turnOnBacklight() {
  digitalWrite(HIGHLIGHT_PIN, HIGH);
}

void turnOffBacklight() {
  digitalWrite(HIGHLIGHT_PIN, LOW);
}

void playSound() {
  tone(BUZZER_PIN, 440, 200);
}
