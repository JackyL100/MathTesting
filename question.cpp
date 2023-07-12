#include "question.hpp"

Question::Question(int new_first, int new_second) {
    first = new_first;
    second = new_second;
}

bool Question::check() {
    correct = student_answer == first * second;
}

void Question::getStudentAnswer() {
    std::cin >> student_answer;
    cv.notify_one();
}