#pragma once
#include "game.h"

void showWelcome(int highScore);
void getGameSettings(int& min, int& max, int& duration, int& mode);
void showResults(const Game& game, int highScore, bool newHighScore);
void showHighScore(int highScore); 