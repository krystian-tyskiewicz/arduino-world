#include "PlayersSettingsView.h"
#include "Game.h"

PlayersSettingsView::PlayersSettingsView(MCUFRIEND_kbv &display, Game &g) :
  tft(display),
  game(g) {}

void PlayersSettingsView::draw() {
  tft.fillScreen(WHITE);
  tft.drawLine(0, 120, 240, 120, BLACK);
  tft.drawLine(120, 0, 120, 240, BLACK);
  tft.drawLine(240, 0, 240, 240, BLACK);

  drawPlayer(0, 10, 10);
  drawPlayer(1, 130, 10);
  drawPlayer(2, 10, 130);
  drawPlayer(3, 130, 130);

  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.setCursor(250, 10);
  tft.print("Wstecz");
  
  tft.drawLine(240, 30, 320, 30, BLACK);
}

void PlayersSettingsView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 240 && screenPoint.y > 0 && screenPoint.y < 30) {
        game.goToSettings();
    }
    if (screenPoint.x < 120 && screenPoint.y < 120) {
        game.goToPlayerSettings(0);
    }
    if (screenPoint.x > 120 && screenPoint.x < 240 && screenPoint.y < 120) {
        game.goToPlayerSettings(1);
    }
    if (screenPoint.x < 120 && screenPoint.y > 120) {
        game.goToPlayerSettings(2);
    }
    if (screenPoint.x > 120 && screenPoint.x < 240 && screenPoint.y > 120) {
        game.goToPlayerSettings(3);
    }
}

void PlayersSettingsView::drawPlayer(int playerIndex, int x, int y) {
    tft.setTextColor(game.getPlayer(playerIndex).active ? game.getPlayer(playerIndex).color : BLACK);
    tft.setTextSize(2);
    tft.setCursor(x, y);
    tft.print(game.getPlayer(playerIndex).name);
}
