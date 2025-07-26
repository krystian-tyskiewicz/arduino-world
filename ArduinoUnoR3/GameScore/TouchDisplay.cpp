#include "TouchDisplay.h"

#define YP A2
#define XM A3
#define YM 8
#define XP 9

#define TS_MINX 106
#define TS_MAXX 946
#define TS_MINY 112
#define TS_MAXY 904

#define MINPRESSURE 1
#define MAXPRESSURE 1000

TouchDisplay::TouchDisplay(MCUFRIEND_kbv &display)
    : ts(XP, YP, XM, YM, 300), tft(display) {}

ScreenPoint TouchDisplay::getScreenPoint() {
    TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        return convertTouchToScreen(p.x, p.y);
    }
    return ScreenPoint{-1, -1};
}

ScreenPoint TouchDisplay::convertTouchToScreen(int x, int y) {
    int tftWidth = tft.width();
    int tftHeight = tft.height();
    ScreenPoint screenPoint;
    screenPoint.x = tftWidth - map(x, TS_MINX, TS_MAXX, 0, tftWidth);
    screenPoint.y = tftHeight - map(y, TS_MINY, TS_MAXY, 0, tftHeight);
    return screenPoint;
}
