#include "Keyboard.h"

Keyboard::Keyboard(MCUFRIEND_kbv &display, int startY)
    : tft(display),
      keyboardRow1("QWERTYUIOP"),
      keyboardRow2("ASDFGHJKL"),
      keyboardRow3("ZXCVBNM<"),
      padding(4),
      startY(startY),
      keyWidth(28),
      keyHeight(30),
      keyCount(0) {}

void Keyboard::draw() {
    tft.setTextSize(2);
    tft.setTextColor(BLACK);

    for (int i = 0; i < strlen(keyboardRow1); i++) {
        int x = i * (keyWidth + padding) + 2;
        int y = startY;
        drawKey(x, y, keyWidth, keyHeight, keyboardRow1[i]);
    }

    for (int i = 0; i < strlen(keyboardRow2); i++) {
        int x = i * (keyWidth + padding) + keyWidth / 2;
        int y = startY + keyHeight + padding;
        drawKey(x, y, keyWidth, keyHeight, keyboardRow2[i]);
    }

    for (int i = 0; i < strlen(keyboardRow3); i++) {
        int x = i * (keyWidth + padding) + keyWidth + 2;
        int y = startY + 2 * (keyHeight + padding);
        drawKey(x, y, keyWidth, keyHeight, keyboardRow3[i]);
    }
}

void Keyboard::handleScreenPoint(ScreenPoint screenPoint) {
    char pressed = getKeyAt(screenPoint.x, screenPoint.y);
    if (pressed) {
        if (pressed == '<' && typedText.length() > 0) {
            typedText.remove(typedText.length() - 1);
        } else if (pressed != '<' && typedText.length() < maxTypedText) {
            typedText += pressed;
        }
        delay(200);
    }
}

String Keyboard::getTypedText() {
    return typedText;
}

void Keyboard::clearTypedText() {
    typedText = "";
}

void Keyboard::setTypedText(String text) {
    typedText = text;
}

char Keyboard::getKeyAt(int x, int y) {
    for (int i = 0; i < keyCount; i++) {
        if (x >= keyPositions[i][0] && x <= keyPositions[i][0] + keyWidth &&
            y >= keyPositions[i][1] && y <= keyPositions[i][1] + keyHeight) {
            return keyLabels[i];
        }
    }
    return 0;
}

void Keyboard::drawKey(int x, int y, int w, int h, char c) {
    tft.drawRect(x, y, w, h, BLACK);
    int textX = x + (w - 12) / 2;
    int textY = y + (h - 16) / 2;
    tft.setCursor(textX, textY);
    tft.print(c);

    if (keyCount < MAX_KEYS) {
        keyPositions[keyCount][0] = x;
        keyPositions[keyCount][1] = y;
        keyLabels[keyCount] = c;
        keyCount++;
    }
}
