#include "random.hpp"

RandomNumberGenerator::RandomNumberGenerator() {

}

int RandomNumberGenerator::generate() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range
    return distr(gen);
}

int RandomNumberGenerator::generate(int temp_min, int temp_max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(temp_min, temp_max); // define the range
    return distr(gen);
}

void RandomNumberGenerator::setRange(int new_min, int new_max) {
    min = new_min;
    max = new_max;
}