#include "question.hpp"

Question::Question(int new_first, int new_second) {
    first = new_first;
    second = new_second;
}

bool Question::check(int time) {
    // correct = (student_answer == first * second) && (time < 5000000);
    // return correct;
    bool correct_answer = student_answer = first * second;
    bool slow = time > 5000000;
    if (!correct_answer && slow) {
        reason = "Wrong and Slow";
    } else if (!correct_answer) {
        reason = "Wrong Answer";
    } else if (slow) {
        reason = "Too Slow";
    }
    correct = correct_answer && !slow;
    return correct;
}

void Question::getStudentAnswer() {
    //t1 = std::thread([this](){std::cin >> student_answer; cv.notify_one();});
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::string answer;
    std::getline(std::cin, answer);
    student_answer = answer.empty() ? -1 : std::stoi(answer);
}