#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <MCUFRIEND_kbv.h>
#include "Common.h"

class Game;

class SettingsView : public View {
public:
    SettingsView(MCUFRIEND_kbv &display, Game &g);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);

private:
    MCUFRIEND_kbv &tft;
    Game &game;
};

#endif
