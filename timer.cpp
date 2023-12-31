#include "timer.hpp"

void Timer::SetTimer(int time) {
    auto start = std::chrono::system_clock::now();
    while (1) {
        const auto now = std::chrono::system_clock::now();
        const auto duration = now - start;
        if ( duration.count() > time * 1000000) {
            break;
        }

    } 
    std::cout << "done" << std::endl;
}

void Timer::makeNewQuestion() {
    currentQuestion = std::make_unique<Question>(numGen.generate(), numGen.generate());
}

void Timer::askQuestion() {
    std::cout << currentQuestion->first << " x " << currentQuestion->second << " = ";
}