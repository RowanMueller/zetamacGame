#include "game.h"
#include "ui.h"
#include "utils.h"
#include <chrono>
#include <iostream>

Game::Game(int min, int max, int duration, int mode)
    : min(min), max(max), duration(duration), mode(mode) {}

void Game::start() {
    if (isTimeTrial()) {
        timeTrialLoop();
        return;
    }
    auto start_time = std::chrono::steady_clock::now();
    while (true) {
        auto now = std::chrono::steady_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
        if (elapsed >= duration) break;
        askQuestion();
    }
}

bool Game::isTimeTrial() const {
    return mode == 5;
}

void Game::timeTrialLoop() {
    const int questionTime = 10; // seconds per question
    bool running = true;
    while (running) {
        auto q_start = std::chrono::steady_clock::now();
        int a, b, answer, userAnswer;
        char op;
        bool valid = false;
        while (!valid) {
            a = randomInt(min, max);
            b = randomInt(min, max);
            switch (mode) {
                case 1: op = '+'; answer = a + b; valid = true; break;
                case 2: op = '-'; answer = a - b; valid = true; break;
                case 3: op = '*'; answer = a * b; valid = true; break;
                case 4: op = '/'; if (b != 0 && a % b == 0) { op = '/'; answer = a / b; valid = true; } break;
                case 5: { // Time trial: allow all operations
                    int opType = randomInt(1, 4);
                    switch (opType) {
                        case 1: op = '+'; answer = a + b; valid = true; break;
                        case 2: op = '-'; answer = a - b; valid = true; break;
                        case 3: op = '*'; answer = a * b; valid = true; break;
                        case 4: if (b != 0 && a % b == 0) { op = '/'; answer = a / b; valid = true; } break;
                    }
                    break;
                }
                default: op = '?'; valid = false; break;
            }
        }
        std::cout << a << " " << op << " " << b << " = ";
        bool answered = false;
        while (!answered) {
            auto now = std::chrono::steady_clock::now();
            int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - q_start).count();
            if (elapsed >= questionTime) {
                std::cout << "\nTime's up!\n";
                running = false;
                break;
            }
            if (std::cin.rdbuf()->in_avail() > 0) {
                std::cin >> userAnswer;
                if (userAnswer == answer) {
                    std::cout << "Correct!\n";
                    score++;
                    total++;
                    answered = true;
                } else {
                    std::cout << "Incorrect. The answer was " << answer << ".\n";
                    total++;
                    answered = true;
                }
            }
        }
    }
}

void Game::askQuestion() {
    int a, b, answer, userAnswer;
    char op;
    bool valid = false;
    while (!valid) {
        a = randomInt(min, max);
        b = randomInt(min, max);
        switch (mode) {
            case 1: // Addition
                op = '+';
                answer = a + b;
                valid = true;
                break;
            case 2: // Subtraction
                op = '-';
                answer = a - b;
                valid = true;
                break;
            case 3: // Multiplication
                op = '*';
                answer = a * b;
                valid = true;
                break;
            case 4: // Division
                op = '/';
                if (b != 0 && a % b == 0) {
                    answer = a / b;
                    valid = true;
                }
                break;
            default:
                op = '?';
                valid = false;
        }
    }
    std::cout << a << " " << op << " " << b << " = ";
    std::cin >> userAnswer;
    if (userAnswer == answer) {
        std::cout << "Correct!\n";
        score++;
    } else {
        std::cout << "Incorrect. The answer was " << answer << ".\n";
    }
    total++;
}

int Game::getScore() const { return score; }
int Game::getTotal() const { return total; }
int Game::getDuration() const { return duration; }
int Game::getMode() const { return mode; } 