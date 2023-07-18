#ifndef TEST_HPP
#define TEST_HPP


#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>
#include <functional>
#include <vector>
#include <memory>
#include <string>
#include "question.hpp"
#include "random.hpp"

// level One : only single digit
// level Two : 2 and single digit
// level Three: both 2 digit

enum class Level {
    One, 
    Two,
    Three
};

class Test {

    private:

        RandomNumberGenerator numGen;

        int min, max;

    public:

        std::vector<std::unique_ptr<Question>> incorrectQuestions;

        std::string student;

        std::string possibleOperations;

        int numCorrect = 0;
        int numQuestions = 0;

        Level difficulty;

        std::unique_ptr<Question> currentQuestion;

        Test(std::string operations, std::string student_name, int level);

        //template<typename T>
        int questionElapsedTime() {
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
            currentQuestion->getStudentAnswer();
            std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
            auto duration = end - start;
            return duration.count();
        }

        virtual void makeNewQuestion();

        void askQuestion();

        void printIncorrectQuestions();
};

#endif