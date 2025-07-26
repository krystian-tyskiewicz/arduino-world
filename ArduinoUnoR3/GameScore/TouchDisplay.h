#ifndef TOUCHDISPLAY_H
#define TOUCHDISPLAY_H

#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "Common.h"

class TouchDisplay {
public:
    TouchDisplay(MCUFRIEND_kbv &display);
    ScreenPoint getScreenPoint();

private:
    TouchScreen ts;
    MCUFRIEND_kbv &tft;
    ScreenPoint convertTouchToScreen(int x, int y);
};

#endif
