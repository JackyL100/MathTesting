#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>


class Question {

    public:

        int first;

        int second;

        bool correct;

        int student_answer;

        std::string reason;

        Question(int new_first, int new_second);

        bool check(int time);

        void getStudentAnswer();

};