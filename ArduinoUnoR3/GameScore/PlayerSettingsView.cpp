#include "PlayerSettingsView.h"
#include "GameView.h"
#include "Game.h"

PlayerSettingsView::PlayerSettingsView(MCUFRIEND_kbv &display, Game &g) :
    tft(display),
    game(g),
    keyboard(display, 50) {
        
    }

void PlayerSettingsView::draw() {
    tft.fillScreen(WHITE);

    tft.setTextSize(2);
    tft.setCursor(10, 160);
    tft.print("Zapisz");

    keyboard.setTypedText(String(game.getCurrentPlayer().name));
    keyboard.draw();
    drawNewName();
    drawIsActive();
}

void PlayerSettingsView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 10 && screenPoint.x < 82 && screenPoint.y > 160 && screenPoint.y < 184) {
        game.getCurrentPlayer().name = keyboard.getTypedText();
        game.goToPlayersSettings();
  
        return;
    }

    if (screenPoint.x > 10 && screenPoint.x < 82 && screenPoint.y > 190 && screenPoint.y < 204) {
        game.getCurrentPlayer().active = !game.getCurrentPlayer().active;
        game.goToPlayersSettings();
  
        return;
    }

    keyboard.handleScreenPoint(screenPoint);
    drawNewName();
    drawIsActive();
}

void PlayerSettingsView::drawNewName() {
    tft.fillRect(0, 0, 320, 50, WHITE);
    tft.setCursor(10, 10);
    tft.setTextSize(3);
    tft.setTextColor(game.getCurrentPlayer().color);
    tft.print(keyboard.getTypedText());
}

void PlayerSettingsView::drawIsActive() {
    tft.fillRect(0, 190, 320, 24, WHITE);
    tft.setCursor(10, 190);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.print(game.getCurrentPlayer().active ? "Wylacz" : "Wlacz");
}
