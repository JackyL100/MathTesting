#include <iostream>
#include <thread>
#include "timer.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <utility>

// make timer have a unique ptr to a question then change the question every time

int main(int argc, char* argv[]) {
    Timer t;

    while (t.numQuestions < atoi(argv[1])) {
        t.makeNewQuestion();
        t.askQuestion();
        //question->getStudentAnswer();
        if (t.currentQuestion->check(t.questionElapsedTime())) {
            t.numCorrect++;
        } else {
            t.incorrectQuestions.push_back(std::move(t.currentQuestion));
        }
        t.numQuestions++;
    }

    std::cout << "Total Score: " << (double)t.numCorrect / t.numQuestions << "\n";
    
    for (int i = 0; i < t.incorrectQuestions.size(); i++) {
        std::cout << i + 1 << ") " << t.incorrectQuestions[i]->first << " x " << t.incorrectQuestions[i]->second << " = " << t.incorrectQuestions[i]->reason << "\n";
    }
    
    //t.elapsedTime<void(*)()>(busywork);
}