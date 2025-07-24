#include "ui.h"
#include <iostream>

void showWelcome(int highScore) {
    std::cout << "\n=== Zetamac Arithmetic Game ===\n";
    std::cout << "Current High Score: " << highScore << "\n";
}

void getGameSettings(int& min, int& max, int& duration, int& mode) {
    std::cout << "Enter minimum number: ";
    std::cin >> min;
    std::cout << "Enter maximum number: ";
    std::cin >> max;
    std::cout << "Enter game duration (seconds, ignored for Time Trial): ";
    std::cin >> duration;
    std::cout << "Select mode (1=Add, 2=Sub, 3=Mul, 4=Div, 5=Time Trial): ";
    std::cin >> mode;
}

void showResults(const Game& game, int highScore, bool newHighScore) {
    std::cout << "\nGame Over!\n";
    std::cout << "Score: " << game.getScore() << "/" << game.getTotal() << "\n";
    std::cout << "High Score: " << highScore << "\n";
    if (newHighScore) {
        std::cout << "Congratulations! New High Score!\n";
    }
}

void showHighScore(int highScore) {
    std::cout << "High Score: " << highScore << "\n";
} 