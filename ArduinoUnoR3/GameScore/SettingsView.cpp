#include "SettingsView.h"
#include "Game.h"

SettingsView::SettingsView(MCUFRIEND_kbv &display, Game &g) : tft(display), game(g) {}

void SettingsView::draw() {
    tft.fillScreen(WHITE);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.setCursor(10, 10);
    tft.print("Ustawienia");

    tft.setTextSize(2);

    tft.setCursor(10, 60);
    tft.print("Punkty");

    tft.setCursor(10, 100);
    tft.print("Gracze");

    tft.setCursor(10, 180);
    tft.print("Wstecz");
}

void SettingsView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.y > 60 && screenPoint.y < 84) {
      game.goToPointsSettings();
    }

    if (screenPoint.y > 100 && screenPoint.y < 124) {
      game.goToPlayersSettings();
    }
  
    if (screenPoint.y > 180 && screenPoint.y < 204) {
      game.goToGameView();
    }
}
