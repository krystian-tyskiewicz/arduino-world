#ifndef GAME_H
#define GAME_H

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include "Common.h"
#include "TouchDisplay.h"
#include "GameView.h"
#include "SettingsView.h"
#include "PlayerView.h"

struct Player {
    const char* name;
    int points = 0;
    int color;
};

struct Settings {
    int points = 301;
};

class Game {
    Player players[4];
    Settings settings;
public:
    Game();

    void begin();
    void loop();

    void goToGameView();
    void goToSettings();
    void goToPlayerView(int playerIndex);

    void drawCurrentView();

    Player getPlayer(int playerIndex);
    Player getCurrentPlayer();

private:
    GameView gameView;
    SettingsView settingsView;
    PlayerView playerView;
    View* view;
    Player* currentPlayer;
};

#endif
