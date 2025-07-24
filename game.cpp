#include "game.h"
#include "utils.h"
#include <sstream>

Game::Game(int min, int max, int duration, int mode)
    : min(min), max(max), duration(duration), mode(mode) {
    nextQuestion();
}

void Game::start() {
    // Not used in GUI version
}

void Game::generateQuestion() {
    bool valid = false;
    while (!valid) {
        currentA = randomInt(min, max);
        currentB = randomInt(min, max);
        switch (mode) {
            case 1: // Addition
                currentOp = '+';
                currentAnswer = currentA + currentB;
                valid = true;
                break;
            case 2: // Subtraction
                currentOp = '-';
                currentAnswer = currentA - currentB;
                valid = true;
                break;
            case 3: // Multiplication
                currentOp = '*';
                currentAnswer = currentA * currentB;
                valid = true;
                break;
            case 4: // Division
                currentOp = '/';
                if (currentB != 0 && currentA % currentB == 0) {
                    currentAnswer = currentA / currentB;
                    valid = true;
                }
                break;
            case 5: { // Time trial: random op
                int opType = randomInt(1, 4);
                switch (opType) {
                    case 1: currentOp = '+'; currentAnswer = currentA + currentB; valid = true; break;
                    case 2: currentOp = '-'; currentAnswer = currentA - currentB; valid = true; break;
                    case 3: currentOp = '*'; currentAnswer = currentA * currentB; valid = true; break;
                    case 4: if (currentB != 0 && currentA % currentB == 0) { currentOp = '/'; currentAnswer = currentA / currentB; valid = true; } break;
                    default: currentOp = '?'; valid = false; break;
                }
                break;
            }
            default:
                currentOp = '?';
                valid = false;
        }
    }
}

std::string Game::getCurrentQuestion() const {
    std::ostringstream oss;
    oss << currentA << " " << currentOp << " " << currentB << " = ";
    return oss.str();
}

bool Game::checkAnswer(int userAnswer) {
    total++;
    if (userAnswer == currentAnswer) {
        score++;
        return true;
    }
    return false;
}

void Game::nextQuestion() {
    generateQuestion();
}

int Game::getScore() const { return score; }
int Game::getTotal() const { return total; }
int Game::getDuration() const { return duration; }
int Game::getMode() const { return mode; }
bool Game::isTimeTrial() const { return mode == 5; } 