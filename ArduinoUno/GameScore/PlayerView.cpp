#include "GameView.h"
#include "Game.h"

PlayerView::PlayerView(MCUFRIEND_kbv &display, Game &g) :
    tft(display),
    game(g),
    numberKeyboard(display, 150) {}

void PlayerView::draw() {
    tft.fillScreen(WHITE);

    tft.setTextColor(game.getCurrentPlayer().color);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.print(game.getCurrentPlayer().name);
    tft.setCursor(10, 40);
    tft.print(game.getCurrentPlayer().points);

    tft.setTextColor(BLACK);
    tft.setCursor(10, 100);
    tft.print("Dodaj");

    tft.setTextColor(BLACK);
    tft.setCursor(10, 190);
    tft.print("Odejmij");

    tft.setTextColor(BLACK);
    tft.setCursor(10, 220);
    tft.print("Ustaw");

    numberKeyboard.draw();
}

void PlayerView::handleScreenPoint(ScreenPoint screenPoint) {
    if (screenPoint.x > 10 && screenPoint.x < 70 && screenPoint.y > 100 && screenPoint.y < 124) {
        game.getCurrentPlayer().points += numberKeyboard.getTypedText().toInt();
        numberKeyboard.clearTypedText();
        game.goToGameView();

        return;
    }

    if (screenPoint.x > 10 && screenPoint.x < 84 && screenPoint.y > 190 && screenPoint.y < 214) {
        game.getCurrentPlayer().points -= numberKeyboard.getTypedText().toInt();
        numberKeyboard.clearTypedText();
        game.goToGameView();

        return;
    }

    if (screenPoint.x > 10 && screenPoint.x < 70 && screenPoint.y > 220 && screenPoint.y < 244) {
        game.getCurrentPlayer().points = numberKeyboard.getTypedText().toInt();
        numberKeyboard.clearTypedText();
        game.goToGameView();

        return;
    }

    numberKeyboard.handleScreenPoint(screenPoint);
    drawNewPoints();
}

void PlayerView::drawNewPoints() {
    tft.fillRect(10, 70, 60, 24, WHITE);
    tft.setCursor(10, 70);
    tft.setTextSize(2);
    tft.setTextColor(game.getCurrentPlayer().color);
    tft.print(numberKeyboard.getTypedText());
}
