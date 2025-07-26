#include "arduino_secrets.h"
#include "thingProperties.h"
//Import libraries
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#include "Arduino_CloudConnectionFeedback.h"

#include <Modulino.h>
#include "Button2.h"
// Creation of objects for Modulino nodes
ModulinoButtons buttons;
ModulinoBuzzer buzzer;
ModulinoPixels pixels;
ModulinoKnob knob;
ModulinoDistance distance;
ModulinoThermo thermo;
ModulinoMovement movement;
//Creation of object for UNO R4 WiFi LED Matrix
ArduinoLEDMatrix matrix;
//Creation on objects for button handling
Button2 button0, button1, button2;

//global varaibles among combinations
String msg;


//messages intervals
unsigned long previousMillis = 0;
const long interval = 1000;
bool intro = false, combo = false, desc = false, reset = false;
unsigned long currentMillis;

uint8_t button0StateHandler() {
  buttons.update();
  return buttons.isPressed(0) ? LOW : HIGH;  // fake a normal button -> LOW = pressed
}
uint8_t button1StateHandler() {
  buttons.update();
  return buttons.isPressed(1) ? LOW : HIGH;  // fake a normal button -> LOW = pressed
}
uint8_t button2StateHandler() {
  buttons.update();
  return buttons.isPressed(2) ? LOW : HIGH;  // fake a normal button -> LOW = pressed
}

//making sure the position of the Modulino Knob remains in range
int position() {
  int pos;
  if (knob.get() % 8 < 0) {
    pos = ((knob.get() % 8) * -1) - 1;
  } else {
    pos = 7 - (knob.get() % 8);
  }
  return pos;
}
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  matrix.begin();
  waitForArduinoCloudConnection(matrix);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you will get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  //Animation to inform connection status
  ArduinoCloud.printDebugInfo();
  //Initialisation of the the Modulino nodes
  Modulino.begin();
  if (!buttons.begin()) { Serial.println("Modulino Buttons not found!"); }
  if (!knob.begin()) { Serial.println("Modulino Knob not found!"); }
  if (!buzzer.begin()) { Serial.println("Modulino Buzzer not found!"); }
  if (!pixels.begin()) { Serial.println("Modulino Pixels not found!"); }
  if (!movement.begin()) { Serial.println("Modulino Movement not found!"); }
  if (!thermo.begin()) { Serial.println("Modulino Thermo not found!"); }
  if (!distance.begin()) { Serial.println("Modulino Distance not found!"); }
  //Set the handlers for the Modulino Buttons
  if (buttons) {
    button0.setButtonStateFunction(button0StateHandler);
    button0.setReleasedHandler(handlerBtn0);
    button0.begin(BTN_VIRTUAL_PIN);
    button1.setButtonStateFunction(button1StateHandler);
    button1.setReleasedHandler(handlerBtn1);
    button1.begin(BTN_VIRTUAL_PIN);
    button2.setButtonStateFunction(button2StateHandler);
    button2.setReleasedHandler(handlerBtn2);
    button2.begin(BTN_VIRTUAL_PIN);
  }
  //Set the Modulino Knob as 0 at the beginning
  if (knob) {
    knob.set(0);
  }
  //Initialize the matrix and start the Tetris and heart animation
  matrix.loadSequence(LEDMATRIX_ANIMATION_TETRIS_INTRO);
  matrix.play(false);
}
void loop() {
  ArduinoCloud.update();
  currentMillis = millis();

  // Your code here
  if (matrix.sequenceDone()) {
    //Send first welcome message to message log
    if (intro == false && currentMillis - previousMillis >= interval) {
      msg_log = "Welcome to the Plug and Make kit!";
      previousMillis = currentMillis;
      intro = true;
    }
    // if Modulino knob and Modulino pixels combo is detected
    if (knob && pixels) {
      //informs the detection
      if (combo == false && currentMillis - previousMillis >= interval) {
        msg_log = "I have found the Modulino Knob + Modulino Pixels";
        previousMillis = currentMillis;
        combo = true;
      }
      //explains the combo
      if (desc == false && currentMillis - previousMillis >= interval) {
        msg_log = "Using the Modulino Knob:\n-Rotate left or right to change the color on the Modulino pixels and shift the animation on LED Matrix.\n-Give it a press to switch LED color and adjust animation direction.";
        previousMillis = currentMillis;
        desc = true;
      }
      //suggest to change the Modulino combo
      if (reset == false && currentMillis - previousMillis >= interval * 5) {
        msg_log = "Mix it up!\nSwap Modulinos.\nWhen ready, press reset on board or dashboard.\nGive it a go!";
        previousMillis = currentMillis;
        reset = true;
      }
      //reset timer
      if (reset && intro && desc && combo) { previousMillis = currentMillis; }
      knobPixels();
      //if Modulino knob and Modulino buzzer combo is detected
    } else if (knob && buzzer) {
      //informs the detection
      if (combo == false && currentMillis - previousMillis >= interval) {
        msg_log = "I have found the Modulino Knob + Modulino Buzzer";
        previousMillis = currentMillis;
        combo = true;
      }
      //explains the combo
      if (desc == false && currentMillis - previousMillis >= interval) {
        msg_log = "Let's play with the Modulino Knob! \n-Twist left or right to adjust sound frequency from the buzzer and switch up the animation. \n-Give it a press to mute the buzzer.\nEasy peasy!";
        previousMillis = currentMillis;
        desc = true;
      }
      //suggest to change the Modulino combo
      if (reset == false && currentMillis - previousMillis >= interval * 5) {
        msg_log = "Mix it up!\nSwap Modulinos.\nWhen ready, press reset on board or dashboard.\nGive it a go!";
        previousMillis = currentMillis;
        reset = true;
      }
      //reset timer
      if (reset && intro && desc && combo) { previousMillis = currentMillis; }
      knobBuzzer();
    } else if (distance && pixels) {
      //informs the detection
      if (combo == false && currentMillis - previousMillis >= interval) {
        msg_log = "I have found the Modulino Distance + Modulino Pixels";
        previousMillis = currentMillis;
        combo = true;
      }
      //explains the combo
      if (desc == false && currentMillis - previousMillis >= interval) {
        msg_log = "Try this:\nHover your hand over Modulino Distance and see Modulino Pixels react to your hand's distance.\nSee distance values in centimeters on UNO R4 WiFi LED matrix.\nGive it a try and see the magic happen!";
        previousMillis = currentMillis;
        desc = true;
      }
      //suggest to change the Modulino combo
      if (reset == false && currentMillis - previousMillis >= interval * 5) {
        msg_log = "Mix it up!\nSwap Modulinos.\nWhen ready, press reset on board or dashboard.\nGive it a go!";
        previousMillis = currentMillis;
        reset = true;
      }
      //reset timer
      if (reset && intro && desc && combo) { previousMillis = currentMillis; }
      distancePixels();
    } else if (buttons && thermo) {
      //informs the detection
      if (combo == false && currentMillis - previousMillis >= interval) {
        msg_log = "I have found the Modulino Buttons + Modulino Thermo";
        previousMillis = currentMillis;
        combo = true;
      }
      //explains the combo
      if (desc == false && currentMillis - previousMillis >= interval) {
        msg_log = "Let's explore Modulino Buttons! \nTwo LEDs show which buttons to press. \nButton A displays temp on UNO R4 WiFi LED matrix, Button C shows humidity. \nGive it a try!";
        previousMillis = currentMillis;
        desc = true;
      }
      //suggest to change the Modulino combo
      if (reset == false && currentMillis - previousMillis >= interval * 5) {
        msg_log = "Mix it up!\nSwap Modulinos.\nWhen ready, press reset on board or dashboard.\nGive it a go!";
        previousMillis = currentMillis;
        reset = true;
      }
      //reset timer
      if (reset && intro && desc && combo) { previousMillis = currentMillis; }
      thermoButtons();
    } else if (buttons && pixels) {
      //informs the detection
      if (combo == false && currentMillis - previousMillis >= interval) {
        msg_log = "I have found the Modulino Buttons + Modulino Pixels";
        previousMillis = currentMillis;
        combo = true;
      }
      //explains the combo
      if (desc == false && currentMillis - previousMillis >= interval) {
        msg_log = "Enjoy this 2-player game! You're Player 1 (Red), your friend's Player 2 (Green) on Modulino Pixels. Tap A to move Player 1, C for Player 2. Goal? Reach the end fast to score. First to 9+ points wins! Ready, set, go!";
        previousMillis = currentMillis;
        desc = true;
      }
      //suggest to change the Modulino combo
      if (reset == false && currentMillis - previousMillis >= interval * 5) {
        msg_log = "Mix it up!\nSwap Modulinos.\nWhen ready, press reset on board or dashboard.\nGive it a go!";
        previousMillis = currentMillis;
        reset = true;
      }
      //reset timer
      if (reset && intro && desc && combo) { previousMillis = currentMillis; }
      buttonsPixels();
    } else if (buttons && movement) {
      //informs the detection
      if (combo == false && currentMillis - previousMillis >= interval) {
        msg_log = "I have found the Modulino Buttons + Modulino Movement";
        previousMillis = currentMillis;
        combo = true;
      }
      //explains the combo
      if (desc == false && currentMillis - previousMillis >= interval) {
        msg_log = "Use Modulino Movement to guide your character at the LED Matrix bottom. Press button B on Modulino Button to smash targets atop. Let's conquer!";
        previousMillis = currentMillis;
        desc = true;
      }
      //suggest to change the Modulino combo
      if (reset == false && currentMillis - previousMillis >= interval * 5) {
        msg_log = "Mix it up!\nSwap Modulinos.\nWhen ready, press reset on board or dashboard.\nGive it a go!";
        previousMillis = currentMillis;
        reset = true;
      }
      //reset timer
      if (reset && intro && desc && combo) { previousMillis = currentMillis; }
      movementButton();
    } else {
      //No Modulino found
      if (combo == false && currentMillis - previousMillis >= interval) {
        msg_log = "I haven't found any Modulino combinations ";
        previousMillis = currentMillis;
        combo = true;
      }
      if (desc == false && currentMillis - previousMillis >= interval) {
        msg_log = "Looks like no Modulino combination is connected right now. Don't worry!\nMake sure the Modulino nodes are properly connected and reset the board.\nIf you need more help, find more information at arduino.cc/plug-and-make-kit.";
        previousMillis = currentMillis;
        desc = true;
      }

      matrix.beginDraw();
      matrix.stroke(0xFFFFFFFF);
      matrix.textScrollSpeed(80);
      const char text[] = "    Connect a Modulino combination!";
      matrix.textFont(Font_5x7);
      matrix.beginText(0, 1, 0xFFFFFF);
      matrix.println(text);
      matrix.endText(SCROLL_LEFT);
      matrix.endDraw();
    }
  } else {
    //clear message log while the tetris animation is playing
    msg_log = PropertyActions::CLEAR;
    //reset timer
    previousMillis = currentMillis;
  }
}
/***
MODULINO BUZZER + MODULINO KNOB COMBINATION
***/

int frameDuration = 50;
byte frame[8][12];

void knobBuzzer() {
  //call wave function to paint in the LED matrix (functiond defined at the bottom)
  advanceWaveform();
  matrix.renderBitmap(frame, 8, 12);
  delay(frameDuration);
  //control Modulino buzzzer with Modulino Knob position
  if (knob.isPressed()) {
    buzzer.noTone();
  } else {
    buzzer.tone(map(position(), 8, 0, 200, 440), 250);
  }
}

void advanceWaveform() {
  for (int y = 0; y <= 7; y++) {
    for (int x = 0; x <= 11 - 1; x++) {
      if (frame[y][x + 1] == 1) {
        frame[y][x] = 1;
        frame[y][x + 1] = 0;
      } else {
        frame[y][x] = 0;
      }
    }
  }
  frame[position()][11] = 1;
}

/***
MODULINO DISTANCE + MODULINO PIXELS COMBINATION
***/
float dist=0;
void distancePixels() {
  
  if (distance.available()) {
    dist = distance.get();
    int numPixels = map(dist, 400, 20, 8, 0);
    pixels.clear();
    for (int i = 0; i < numPixels; i++) {
      pixels.set(i, 0, 255, 0, 5);
    }
    pixels.show();
    delay(1);
  }
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  char text[4];
  String msg;
  msg = String(dist/10);
  msg.toCharArray(text, 4);
  matrix.textFont(Font_4x6);
  matrix.beginText(1, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();
}

/***
MODULINO BUTTONS + MODULINO PIXELS COMBINATION
***/

int player1 = 0, player2 = 0;
int scorePlayer1 = 0;
int scorePlayer2 = 0;
bool winning = false;
int maxScore = 9;

void handlerBtn0(Button2& btn) {
  player1 = (player1 + 1);
}
void handlerBtn2(Button2& btn) {
  player2 = (player2 + 1);
}
void buttonsPixels() {
  //call handler for Button A and Button C on Modulino Buttons
  button0.loop();
  button2.loop();
  //when the player reach the end add one in the score
  if (player1 == 8) {
    player1 = 0;
    player2 = 0;
    scorePlayer1 += 1;
  }
  if (player2 == 8) {
    player1 = 0;
    player2 = 0;
    scorePlayer2 += 1;
  }
  // if player 1 wins
  if (scorePlayer1 > maxScore) {
    for (int i = 0; i < 8; i++) {
      pixels.set(i, 255, 0, 0, 5);
    }
    pixels.show();
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textFont(Font_4x6);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.textScrollSpeed(70);
    char text[19];
    msg = "   Player 1 wins!";
    msg.toCharArray(text, 17);
    matrix.println(text);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
    winning = true;
  } else if (scorePlayer2 > maxScore) {
    //if player 2 wins
    for (int i = 0; i < 8; i++) {
      pixels.set(i, 0, 255, 0, 5);
    }
    pixels.show();
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textFont(Font_4x6);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.textScrollSpeed(70);
    char text[19];
    msg = "   Player 2 wins!";
    msg.toCharArray(text, 17);
    matrix.println(text);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
    winning = true;
  } else {
    // THE GAME !!!
    buttons.setLeds(true, false, true);
    pixels.clear();
    pixels.set(player1, 255, 0, 0, 10);
    pixels.set(7 - player2, 0, 255, 0, 10);
    pixels.show();
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textFont(Font_4x6);
    matrix.beginText(0, 1, 0xFFFFFF);
    char text[4];
    msg = String(scorePlayer1) + "-" + String(scorePlayer2);
    msg.toCharArray(text, 4);
    matrix.println(text);
    matrix.endText();
  }
  // Initialize all to start the game again
  if (winning) {
    winning = false;
    player1 = 0;
    player2 = 0;
    scorePlayer2 = 0;
    scorePlayer1 = 0;
  }
}
/***
MODULINO KNOB + MODULINO PIXELS COMBINATION
***/

void knobPixels() {
  //Paint diagonal lines pattern on the LED Matrix
  matrix.beginDraw();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      matrix.set(j, i, 0, 0, 0);
    }
  }
  matrix.stroke(0xFFFFFFFF);
  if (knob.isPressed()) {
    for (int i = -11; i < 25; i += 3) {
      matrix.line(i + knob.get() % 8, 0, i + (5 + (knob.get() % 8)), 7);
    }
  } else {
    for (int i = -11; i < 25; i += 3) {
      matrix.line(i - knob.get() % 8, 0, i - (5 + (knob.get() % 8)), 7);
    }
  }
  matrix.endDraw();
  pixels.clear();
  if (knob.isPressed()) {
    // if the Modulino Knob is pressed, only one LED is on and it is controlled by the rotation of the knob
    pixels.set(position(), VIOLET, 10);
  } else {
    //pain a rainbow patter on the LEDs, the rotation on the Modullino Knob moves the color according to the HUE wheel
    for (int i = 0; i < 8; i++) {
      int redValue, greenValue, blueValue;
      int hue = (knob.get() * 20) % 360;
      hueToRGB((hue + i * 45) % 360, redValue, greenValue, blueValue);
      pixels.set(i, redValue, greenValue, blueValue, 10);
    }
  }
  pixels.show();
}

void hueToRGB(int hue, int& r, int& g, int& b) {
  float s = 1.0, v = 1.0;  // Full saturation and value
  int i;
  float f, p, q, t;

  hue = hue % 360;  // Ensure hue is within 0-360

  float h = hue / 60.0;
  i = floor(h);
  f = h - i;
  p = v * (1.0 - s);
  q = v * (1.0 - s * f);
  t = v * (1.0 - s * (1.0 - f));

  switch (i) {
    case 0:
      r = v * 255;
      g = t * 255;
      b = p * 255;
      break;
    case 1:
      r = q * 255;
      g = v * 255;
      b = p * 255;
      break;
    case 2:
      r = p * 255;
      g = v * 255;
      b = t * 255;
      break;
    case 3:
      r = p * 255;
      g = q * 255;
      b = v * 255;
      break;
    case 4:
      r = t * 255;
      g = p * 255;
      b = v * 255;
      break;
    default:
      r = v * 255;
      g = p * 255;
      b = q * 255;
      break;
  }
}
/***
MODULINO MOVEMENT + MODULINO BUTTONS COMBINATION
***/

bool shoot = false;
int currentShootY = 8;
unsigned long previousShootMillis = 0;
unsigned long previousTimerMillis = 0;

const long shootInterval = 50;  // Shooting animation speed
const long timerInterval = 20000;
int shootpos;
int targetPosX = 3, targetPosY = 2;
bool start = false, game = false;
int timeLine = 0;
float valX;

void handlerBtn1(Button2& btn) {
  shoot = true;
  shootpos = valX;
}
float mapF(float x, float in_min, float in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void movementButton() {
  //call button B handler
  button1.loop();
  //update values in Modulino Movement
  movement.update();
  //set the LEDson the Modulino buttons so only button B is on
  buttons.setLeds(false, true, false);
  //Map the values of X between 0 to 12
  valX = mapF(movement.getX(), -1.2, 1.2, 12, 0);
  //Before start, set the timer 0 and clean the score
  if (!start) {
    previousTimerMillis = currentMillis;
    scorePlayer1 = 0;
    start = true;
  }
  if (start) {
    //Start the game, which last as long as timerInterval
    if (currentMillis - previousTimerMillis < timerInterval) {
      // Handle shooting logic
      if (shoot && currentShootY >= 0) {
        if (currentMillis - previousShootMillis > shootInterval) {
          previousShootMillis = currentMillis;  // Update the last shooting time
          currentShootY--;
        }
        if (shootpos == targetPosX && currentShootY <= targetPosY + 1) {
          scorePlayer1++;
          targetPosX = random(2, 10);
          currentShootY = 8;
          shoot = false;
        }
      } else if (shoot) {
        currentShootY = 8;
        shoot = false;
      }
      // Drawing the game state
      matrix.beginDraw();
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 12; j++) {
          matrix.set(j, i, 0, 0, 0);
        }
      }
      matrix.stroke(0xFFFFFFFF);
      //Draw character
      matrix.point(valX, 6);
      matrix.line(valX - 1, 7, valX + 1, 7);
      //Draw target
      matrix.point(targetPosX, targetPosY);
      //Draw bullet
      matrix.point(shootpos, currentShootY);
      timeLine = map(currentMillis - previousTimerMillis, 0, timerInterval, 10, 0);
      matrix.line(0, 0, timeLine, 0);
      matrix.endDraw();
    } else if (currentMillis - previousTimerMillis >= timerInterval && currentMillis - previousTimerMillis < timerInterval + 3000) {
      // Handle score display, it displays for 3 seconds
      msg = String(scorePlayer1);
      matrix.beginDraw();
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 12; j++) {
          matrix.set(j, i, 0, 0, 0);
        }
      }
      matrix.stroke(0xFFFFFFFF);
      char text[3];
      msg.toCharArray(text, 3);
      matrix.textFont(Font_4x6);
      matrix.beginText(3, 1, 0xFFFFFF);
      matrix.println(text);
      matrix.endText();
      matrix.endDraw();
    } else if (currentMillis - previousTimerMillis >= timerInterval + 3000) {
      //Clean the screen and restart the game after the 3 seconds of displaying the score
      matrix.beginDraw();
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 12; j++) {
          matrix.set(j, i, 0, 0, 0);
        }
      }
      matrix.endDraw();
      start = false;
    }
  }
}

/***
MODULINO THERMO + MODULINO BUTTONS COMBINATION
***/

int select = 1;

void thermoButtons() {
  //update data coming from Modulino Buttons
  buttons.update();
  //Set LEDs on Modulino Buttons
  buttons.setLeds(true, false, true);

  if (buttons.isPressed(0)) {
    select = 1;
  }
  if (buttons.isPressed(2)) {
    select = 3;
  }
  if (select == 1) {
    msg = String(thermo.getTemperature()).substring(0, 2) + "C";
  } else if (select == 3) {
    msg = String(thermo.getHumidity()).substring(0, 2) + "%";
  }
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  char text[5];
  msg.toCharArray(text, 5);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();
}

/*
  Since ResetBoard is READ_WRITE variable, onResetBoardChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onResetBoardChange() {
  // Add your code here to act upon ResetBoard change

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(80);
  const char text[] = "  Resetting!  ";
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();

  NVIC_SystemReset();
}

/*
  Since MsgLog is READ_WRITE variable, onMsgLogChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onMsgLogChange() {
  // Add your code here to act upon MsgLog change
}
