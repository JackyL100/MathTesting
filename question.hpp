#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>


class Question {

    public:

        int first;

        int second;

        char operation;

        bool correct;

        int student_answer;

        std::string reason;

        Question(int new_first, int new_second, char op);

        bool check(int time, int max_time);

        void getStudentAnswer();

};

#endif