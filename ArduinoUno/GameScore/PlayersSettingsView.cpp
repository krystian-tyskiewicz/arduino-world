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

  tft.setTextColor(game.getPlayer(0).color);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print(game.getPlayer(0).name);

  tft.setTextColor(game.getPlayer(1).color);
  tft.setTextSize(2);
  tft.setCursor(130, 10);
  tft.print(game.getPlayer(1).name);

  tft.setTextColor(game.getPlayer(2).color);
  tft.setTextSize(2);
  tft.setCursor(10, 130);
  tft.print(game.getPlayer(2).name);

  tft.setTextColor(game.getPlayer(3).color);
  tft.setTextSize(2);
  tft.setCursor(130, 130);
  tft.print(game.getPlayer(3).name);

  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.setCursor(250, 10);
  tft.print("Il. graczy");
  
  tft.drawLine(240, 30, 320, 30, BLACK);

  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.setCursor(250, 40);
  tft.print("Wstecz");

  tft.drawLine(240, 60, 320, 60, BLACK);
}

void PlayersSettingsView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 240 && screenPoint.y > 30 && screenPoint.y < 60) {
        game.goToSettings();
    }
}
