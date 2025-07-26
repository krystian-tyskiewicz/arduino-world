#ifndef PLAYERSETTINGSVIEW_H
#define PLAYERSETTINGSVIEW_H

#include <MCUFRIEND_kbv.h>
#include "Common.h"
#include "Keyboard.h"

class Game;

class PlayerSettingsView : public View {
public:
    PlayerSettingsView(MCUFRIEND_kbv &display, Game &g);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);
    void drawNewName();
    void drawIsActive();

private:
    MCUFRIEND_kbv &tft;
    Game &game;
    Keyboard keyboard;
};

#endif
