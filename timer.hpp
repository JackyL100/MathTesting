#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>
#include <functional>
#include <vector>
#include <memory>
#include "question.hpp"
#include "random.hpp"

class Timer {

    private:

        RandomNumberGenerator numGen;

    public:

        std::vector<std::unique_ptr<Question>> incorrectQuestions;

        int numCorrect = 0;
        int numQuestions = 0;

        void SetTimer(int time);

        std::unique_ptr<Question> currentQuestion;

        //template<typename T>
        int questionElapsedTime() {
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
            currentQuestion->getStudentAnswer();
            std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
            auto duration = end - start;
            return duration.count();
        }

        void makeNewQuestion();

        void askQuestion();


};