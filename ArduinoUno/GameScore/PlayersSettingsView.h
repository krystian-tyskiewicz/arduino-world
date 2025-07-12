#ifndef PLAYERSSETTINGSVIEW_H
#define PLAYERSSETTINGSVIEW_H

#include <MCUFRIEND_kbv.h>
#include "Common.h"

class Game;

class PlayersSettingsView : public View {
public:
    PlayersSettingsView(MCUFRIEND_kbv &display, Game &g);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);

private:
    MCUFRIEND_kbv &tft;
    Game &game;
};

#endif
