#include "GameView.h"
#include "Game.h"

PlayerView::PlayerView(MCUFRIEND_kbv &display, Game &g) :
    tft(display),
    game(g) {}

void PlayerView::draw() {
    tft.fillScreen(WHITE);

    tft.setTextColor(game.getCurrentPlayer().color);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.print(game.getCurrentPlayer().name);
    tft.setCursor(10, 40);
    tft.print(game.getCurrentPlayer().points);
}

void PlayerView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 240 && screenPoint.y < 30) {
        game.goToGameView();
    }
}
