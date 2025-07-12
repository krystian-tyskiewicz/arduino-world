#include "PointsSettingsView.h"
#include "Game.h"

PointsSettingsView::PointsSettingsView(MCUFRIEND_kbv &display, Game &g) :
  tft(display),
  game(g),
  numberKeyboard(display, 150) {
    numberKeyboard.setTypedText(String(g.getSettings().points));
  }

void PointsSettingsView::draw() {
    tft.fillScreen(WHITE);
    tft.setTextColor(BLACK);
    tft.setTextSize(3); 
    tft.setCursor(10, 10);
    tft.print("Punkty");

    tft.setTextSize(2);
    tft.setCursor(10, 140);
    tft.print("Zapisz");

    numberKeyboard.draw();
    drawPoints();
}

void PointsSettingsView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 10 && screenPoint.x < 70 && screenPoint.y > 140 && screenPoint.y < 164) {
      game.getSettings().points = numberKeyboard.getTypedText().toInt();
      game.goToSettings();

      return;
    }

    numberKeyboard.handleScreenPoint(screenPoint);
    drawPoints();
}

void PointsSettingsView::drawPoints() {
  tft.fillRect(10, 100, 60, 24, WHITE);
  tft.setCursor(10, 100);
  tft.setTextSize(2);
  tft.print(numberKeyboard.getTypedText());
}
