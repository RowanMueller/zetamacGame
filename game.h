#pragma once
#include <string>

class Game {
public:
    Game(int min, int max, int duration, int mode);
    void start(); // Not used in GUI, but keep for compatibility
    int getScore() const;
    int getTotal() const;
    int getDuration() const;
    int getMode() const;
    bool isTimeTrial() const;

    // GUI-specific methods
    std::string getCurrentQuestion() const;
    bool checkAnswer(int userAnswer);
    void nextQuestion();

private:
    int min, max, duration, mode;
    int score = 0;
    int total = 0;
    int currentA = 0, currentB = 0, currentAnswer = 0;
    char currentOp = '?';
    void generateQuestion();
}; 