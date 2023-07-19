#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <iostream>
#include <string>
#include <thread>


class Question {

    public:

        double first;

        double second;

        char operation;

        bool correct;

        double student_answer;

        std::string reason;

        Question(double new_first, double new_second, char op);

        bool check(int time, int max_time);

        void getStudentAnswer();

};

#endif