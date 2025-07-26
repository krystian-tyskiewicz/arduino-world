#ifndef POINTSSETTINGSVIEW_H
#define POINTSSETTINGSVIEW_H

#include <MCUFRIEND_kbv.h>
#include "Common.h"
#include "NumberKeyboard.h"

class Game;

class PointsSettingsView : public View {
public:
    PointsSettingsView(MCUFRIEND_kbv &display, Game &g);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);
    void drawPoints();

private:
    MCUFRIEND_kbv &tft;
    Game &game;
    NumberKeyboard numberKeyboard;
};

#endif
