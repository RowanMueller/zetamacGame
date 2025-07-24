#include "game.h"
#include "ui.h"
#include "utils.h"
#include <iostream>

const char* HIGHSCORE_FILE = "highscore.txt";

int main() {
    int highScore = readHighScore(HIGHSCORE_FILE);
    showWelcome(highScore);
    int min, max, duration, mode;
    getGameSettings(min, max, duration, mode);
    Game game(min, max, duration, mode);
    game.start();
    int score = game.getScore();
    bool newHighScore = false;
    if (score > highScore) {
        writeHighScore(HIGHSCORE_FILE, score);
        highScore = score;
        newHighScore = true;
    }
    showResults(game, highScore, newHighScore);
    return 0;
} 