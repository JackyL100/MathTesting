#include "question.hpp"

Question::Question(double new_first, double new_second, char op) {
    first = new_first;
    second = new_second;
    operation = op;
}

bool Question::check(int time, int max_time) {
    bool correct_answer;
    switch (operation) {
        case '+':
            correct_answer = student_answer == first + second;
            break;
        case '-':
            correct_answer = student_answer == first - second;
            break;
        case 'x':
            correct_answer = student_answer == first * second;
            break;
        case '/':
            correct_answer = student_answer == first / second;
            break;
    }
    bool slow = time > max_time * 1000000;
    if (!correct_answer && slow) {
        reason = "Wrong and Slow ";
        reason += std::to_string(time / 1000000) + " seconds";
    } else if (!correct_answer) {
        reason = "Wrong Answer";
    } else if (slow) {
        reason = "Too Slow ";
        reason += std::to_string(time / 1000000) + " seconds";
    }
    correct = correct_answer && !slow;
    return correct;
}

void Question::getStudentAnswer() {
    std::string answer;
    std::cin >> answer;
    student_answer = answer.empty() ? -1 : std::stoi(answer);
}