#include <iostream>
#include <condition_variable>

class Question {

    public:

        int first;

        int second;

        bool correct;

        int student_answer;

        std::condition_variable cv;

        Question(int new_first, int new_second);

        bool check();

        void getStudentAnswer();
};