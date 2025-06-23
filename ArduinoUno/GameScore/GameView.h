#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <MCUFRIEND_kbv.h>
#include "Common.h"

class Game;

class GameView : public View {
public:
    GameView(MCUFRIEND_kbv &display, Game &g);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);

private:
    MCUFRIEND_kbv &tft;
    Game &game;
};

#endif
