#include "GameView.h"
#include "Game.h"

GameView::GameView(MCUFRIEND_kbv &display, Game &g) :
    tft(display),
    game(g) {}

void GameView::draw() {
    tft.fillScreen(WHITE);
    tft.drawLine(0, 120, 240, 120, BLACK);
    tft.drawLine(120, 0, 120, 240, BLACK);
    tft.drawLine(240, 0, 240, 240, BLACK);

    drawPlayer(0, 10, 10, 40);
    drawPlayer(1, 130, 10, 40);
    drawPlayer(2, 10, 130, 160);
    drawPlayer(3, 130, 130, 160);

    tft.setTextColor(BLACK);
    tft.setTextSize(1);
    tft.setCursor(250, 10);
    tft.print("Ustawienia");
    
    tft.drawLine(240, 30, 320, 30, BLACK);

    tft.setTextColor(BLACK);
    tft.setTextSize(1);
    tft.setCursor(250, 40);
    tft.print(game.getSettings().points);

    tft.drawLine(240, 60, 320, 60, BLACK);
}

void GameView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 240 && screenPoint.y < 30) {
        game.goToSettings();
    }
    if (screenPoint.x < 120 && screenPoint.y < 120 && game.getPlayer(0).active) {
        game.goToPlayerView(0);
    }
    if (screenPoint.x > 120 && screenPoint.x < 240 && screenPoint.y < 120 && game.getPlayer(1).active) {
        game.goToPlayerView(1);
    }
    if (screenPoint.x < 120 && screenPoint.y > 120 && game.getPlayer(2).active) {
        game.goToPlayerView(2);
    }
    if (screenPoint.x > 120 && screenPoint.x < 240 && screenPoint.y > 120 && game.getPlayer(3).active) {
        game.goToPlayerView(3);
    }
}

void GameView::drawPlayer(int playerIndex, int x, int nameY, int pointsY) {
    if (!game.getPlayer(playerIndex).active) {
        return;
    }
    tft.setTextColor(game.getPlayer(playerIndex).color);
    tft.setTextSize(2);
    tft.setCursor(x, nameY);
    tft.print(game.getPlayer(playerIndex).name);
    tft.setCursor(x, pointsY);
    tft.print(game.getPlayer(playerIndex).points);
}
