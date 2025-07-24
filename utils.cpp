#include "utils.h"
#include <random>
#include <fstream>

int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int readHighScore(const char* filename) {
    std::ifstream file(filename);
    int score = 0;
    if (file >> score) {
        return score;
    }
    return 0;
}

void writeHighScore(const char* filename, int score) {
    std::ofstream file(filename);
    if (file) {
        file << score;
    }
} 