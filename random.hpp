#include <random>

class RandomNumberGenerator {

    int max = 10;

    int min = 0;

    public: 

    RandomNumberGenerator();

    void setRange(int new_min, int new_max);

    int generate();

};
