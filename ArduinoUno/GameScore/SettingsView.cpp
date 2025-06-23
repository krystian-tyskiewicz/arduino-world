#include "SettingsView.h"
#include "Game.h"

SettingsView::SettingsView(MCUFRIEND_kbv &display, Game &g) : tft(display), game(g) {}

void SettingsView::draw() {
    tft.fillScreen(WHITE);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.setCursor(10, 10);
    tft.print("Ustawienia");
}

void SettingsView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 240 && screenPoint.y < 30) {
      game.goToGameView();
    }
}
