#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include "Common.h"

class Keyboard {
public:
    Keyboard(MCUFRIEND_kbv &display, int startY);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);
    String getTypedText();
    void clearTypedText();
    void setTypedText(String text);
    char getKeyAt(int x, int y);

private:
    MCUFRIEND_kbv &tft;

    const char* keyboardRow1;
    const char* keyboardRow2;
    const char* keyboardRow3;

    static const int MAX_KEYS = 30;

    int padding;
    int startY;
    int keyWidth;
    int keyHeight;
    int keyCount;

    int keyPositions[MAX_KEYS][2];
    char keyLabels[MAX_KEYS];

    String typedText = "";
    int maxTypedText = 8;

    void drawKey(int x, int y, int w, int h, char c);
};

#endif
