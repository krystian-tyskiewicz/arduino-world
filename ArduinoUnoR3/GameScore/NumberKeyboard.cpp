#include "NumberKeyboard.h"

NumberKeyboard::NumberKeyboard(MCUFRIEND_kbv &display, int startX)
    : tft(display),
      padding(4),
      startX(startX),
      startY(40),
      keyWidth(50),
      keyHeight(40),
      keyCount(0) {}

void NumberKeyboard::draw() {
    tft.setTextSize(2);
    tft.setTextColor(BLACK);

    const char keys[3][3] = {
        { '1', '2', '3' },
        { '4', '5', '6' },
        { '7', '8', '9' }
    };

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            int x = startX + col * (keyWidth + padding);
            int y = startY + row * (keyHeight + padding);
            drawKey(x, y, keyWidth, keyHeight, keys[row][col]);
        }
    }

    int zeroX = startX + (keyWidth + padding);
    int zeroY = startY + 3 * (keyHeight + padding);
    drawKey(zeroX, zeroY, keyWidth, keyHeight, '0');

    int delX = startX + 2 * (keyWidth + padding);
    int delY = startY + 3 * (keyHeight + padding);
    drawKey(delX, delY, keyWidth, keyHeight, '<');

}

void NumberKeyboard::handleScreenPoint(ScreenPoint screenPoint) {
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

String NumberKeyboard::getTypedText() {
    return typedText;
}

void NumberKeyboard::clearTypedText() {
    typedText = "";
}

void NumberKeyboard::setTypedText(String text) {
    typedText = text;
}

char NumberKeyboard::getKeyAt(int x, int y) {
    for (int i = 0; i < keyCount; i++) {
        if (x >= keyPositions[i][0] && x <= keyPositions[i][0] + keyWidth &&
            y >= keyPositions[i][1] && y <= keyPositions[i][1] + keyHeight) {
            return keyLabels[i];
        }
    }
    return 0;
}

void NumberKeyboard::drawKey(int x, int y, int w, int h, char c) {
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
