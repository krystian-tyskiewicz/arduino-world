#include "Game.h"

MCUFRIEND_kbv tft;
TouchDisplay td(tft);

Game::Game() :
    gameView(tft, *this),
    settingsView(tft, *this),
    playerView(tft, *this)
{
    players[0].name = "Gracz 1";
    players[0].points = 0;
    players[0].color = BLUE;
    players[1].name = "Gracz 2";
    players[1].points = 0;
    players[1].color = GREEN;
    players[2].name = "Gracz 3";
    players[2].points = 0;
    players[2].color = ORANGE;
    players[3].name = "Gracz 4";
    players[3].points = 0;
    players[3].color = RED;
}

void Game::begin() {
    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);

    goToGameView();
}

void Game::loop() {
    ScreenPoint screenPoint = td.getScreenPoint();
    if (screenPoint.x != -1 && screenPoint.y != -1) {
      view->handleScreenPoint(screenPoint);
    }
}

void Game::goToGameView() {
    view = &gameView;
    drawCurrentView();
}

void Game::goToSettings() {
    view = &settingsView;
    drawCurrentView();
}

void Game::goToPlayerView(int playerIndex) {
    view = &playerView;
    currentPlayer = &players[playerIndex];
    drawCurrentView();
}

void Game::drawCurrentView() {
    view->draw();
}

Player& Game::getPlayer(int playerIndex) {
    return players[playerIndex];
}

Player& Game::getCurrentPlayer() {
    return *currentPlayer;
}
