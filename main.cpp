#include <iostream>
#include <thread>
#include "timer.hpp"
#include "random.hpp"
#include "question.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <utility>

int main(int argc, char* argv[]) {
    
    RandomNumberGenerator numGen;
    std::vector<std::unique_ptr<Question>> incorrectQuestions;

    int numCorrect = 0;
    int numQuestions = 0;

    while (true) {
        
        std::unique_ptr<Question> question = std::make_unique<Question>(numGen.generate(), numGen.generate());
        std::cout << question->first << " x " << question->second << " = ";
        std::thread t1(Question::getStudentAnswer, question.get());
        std::mutex mtx;
        std::unique_lock<std::mutex> lck(mtx);
        while (question->cv.wait_for(lck, std::chrono::seconds(2)) == std::cv_status::timeout) {}
        t1.join();
        if (question->check()) {
            numCorrect++;
        } else {
            incorrectQuestions.push_back(std::move(question));
        }
        numQuestions++;
    }

    std::cout << "Total Score: " << numCorrect / numQuestions << "\n";
    
    for (int i = 0; i < incorrectQuestions.size(); i++) {
        std::cout << i << ") " << incorrectQuestions[i]->first << " x " << incorrectQuestions[i]->second << " = \n";
    }
}