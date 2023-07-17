#include <iostream>
#include <thread>
#include "timer.hpp"
#include "test.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <utility>
#include <fstream>

// argv order: student name, number of questions, time per question, level, operation(s)

int main(int argc, char* argv[]) {

    int level = atoi(argv[4]);
    std::string name(argv[1]);
    std::string operations(argv[5]);
    Test t(operations, name);

    while (t.numQuestions < atoi(argv[2])) {
        t.makeNewQuestion();
        t.askQuestion();
        //question->getStudentAnswer();
        if (t.currentQuestion->check(t.questionElapsedTime(), atoi(argv[3]))) {
            t.numCorrect++;
        } else {
            t.incorrectQuestions.push_back(std::move(t.currentQuestion));
        }
        t.numQuestions++;
    }

    std::cout << "Total Score: " << 100 * (double)t.numCorrect / t.numQuestions << "\n";
    
    if (t.incorrectQuestions.size() > 0) std::cout << "Incorrect Questions:\n";
    for (int i = 0; i < t.incorrectQuestions.size(); i++) {
        std::cout << i + 1 << ") " << t.incorrectQuestions[i]->first << " x " << t.incorrectQuestions[i]->second << " = " << t.incorrectQuestions[i]->reason << "\n";
    }

    
    std::ofstream outf {"/Users/jackylei/Desktop/StudentTestData/" + t.student, std::ios::app};
    if (!outf) {
        std::cerr << "File could not be opened for writing\n";
        return 1;
    }   
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    outf << "\n" << std::ctime(&end_time) << 100 * (double)t.numCorrect / t.numQuestions << "\n";
    outf.close();
}