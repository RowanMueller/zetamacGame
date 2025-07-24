#pragma once
#include <vector>
#include <string>

class Game {
public:
    Game(int min, int max, int duration, int mode);
    void start();
    int getScore() const;
    int getTotal() const;
    int getDuration() const;
    int getMode() const;
    bool isTimeTrial() const;
private:
    int min, max, duration, mode;
    int score = 0;
    int total = 0;
    void askQuestion();
    void timeTrialLoop();
}; 