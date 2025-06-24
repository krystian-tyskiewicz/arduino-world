#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <MCUFRIEND_kbv.h>
#include "Common.h"
#include "NumberKeyboard.h"

class PlayerView;

class PlayerView : public View {
public:
    PlayerView(MCUFRIEND_kbv &display, Game &g);
    void draw();
    void handleScreenPoint(ScreenPoint screenPoint);

private:
    MCUFRIEND_kbv &tft;
    Game &game;
    NumberKeyboard numberKeyboard;
    void drawNewPoints();
};

#endif
