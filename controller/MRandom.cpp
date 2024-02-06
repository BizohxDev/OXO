#include "MRandom.hpp"
#include <random>

int randomInt(int lowerBound, int upperBound){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
    return distribution(generator);
}