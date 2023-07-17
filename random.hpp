#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class RandomNumberGenerator {

    int max = 12;

    int min = 0;

    public: 

    RandomNumberGenerator();

    void setRange(int new_min, int new_max);

    int generate();

    int generate(int temp_min, int temp_max);

    template<typename T>
    T generate(std::vector<T>& vec) {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, vec.size()-1); // define the range
        return vec[distr(gen)];
    }
};

#endif