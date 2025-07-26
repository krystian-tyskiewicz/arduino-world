#ifndef NUMBER_KEYBOARD_H
#define NUMBER_KEYBOARD_H

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include "Common.h"

class NumberKeyboard {
public:
    NumberKeyboard(MCUFRIEND_kbv &display, int startX);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);
    String getTypedText();
    void clearTypedText();
    void setTypedText(String text);
    char getKeyAt(int x, int y);

private:
    MCUFRIEND_kbv &tft;

    static const int MAX_KEYS = 12;

    int padding;
    int startY;
    int startX;
    int keyWidth;
    int keyHeight;
    int keyCount;

    int keyPositions[MAX_KEYS][2];
    char keyLabels[MAX_KEYS];

    String typedText = "";
    int maxTypedText = 4;

    void drawKey(int x, int y, int w, int h, char c);
};

#endif
