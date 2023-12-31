#include <iostream>
#include <thread>
#include "timer.hpp"
#include "test.hpp"
#include <memory>
#include <vector>
#include <mutex>
#include <utility>
#include <fstream>

// argv order: student name, number of questions, time per question, level, operation(s), set range flag


void getInfo(std::vector<std::string>& arg) {
    std::cout << "Who? ";
    std::cin >> arg[1];
    std::cout << "How many questions? ";
    std::cin >> arg[2];
    std::cout << "Time Limit? ";
    std::cin >> arg[3];
    std::cout << "Difficulty? ";
    std::cin >> arg[4];
    std::cout << "Operations? ";
    std::cin >> arg[5];
    std::cout << "Would you like to set a range for the numbers? ";
    std::cin >> arg[6];
}

bool isWhole(double num) {
    return num - (int)num == 0.0;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> new_argv(7);

    if (argc != 7) {
        getInfo(new_argv);
    } else {
        for (int i = 0; i < argc; i++) {
            new_argv[i] = argv[i];
        }
    }

    const int level = std::stoi(new_argv[4]);
    const std::string name = new_argv[1];
    const std::string operations = new_argv[5];
    const int time_limit = std::stoi(new_argv[3]);
    Test t(operations, name, level);
    if (new_argv[6] == "y") {
        t.setCustomRange();
    }

    while (t.numQuestions < std::stoi(new_argv[2])) {
        t.makeNewQuestion();
        t.askQuestion();
        if (t.currentQuestion->check(t.questionElapsedTime(), time_limit)) {
            t.numCorrect++;
        } else {
            t.incorrectQuestions.push_back(std::move(t.currentQuestion));
        }
        t.numQuestions++;
    }

    std::cout << "Total Score: " << 100 * (double)t.numCorrect / t.numQuestions << "\n";

    std::ofstream outf {"/Users/jackylei/Desktop/StudentTestData/" + t.student, std::ios::app};
    if (!outf) {
        std::cerr << "File could not be opened for writing\n";
        return 1;
    }   
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    outf << "\n" << std::ctime(&end_time) << "\nScore: " << 100 * (double)t.numCorrect / t.numQuestions << "\nOperation(s): " << operations << "\nLevel: " << level << "\nTime Limit: " << time_limit << "\n";

    if (t.incorrectQuestions.size() > 0) std::cout << "Incorrect Questions:\n";
    for (int i = 0; i < t.incorrectQuestions.size(); i++) {
        std::string statement = "";
        statement += std::to_string(i + 1);
        statement += ") ";
        if (isWhole(t.incorrectQuestions[i]->first)) {
            statement += std::to_string((int)t.incorrectQuestions[i]->first);
        } else {
            statement += std::to_string(t.incorrectQuestions[i]->first);
        }
        statement += " ";
        statement += t.incorrectQuestions[i]->operation;
        statement += " ";
        if (isWhole(t.incorrectQuestions[i]->first)) {
            statement += std::to_string((int)t.incorrectQuestions[i]->second);
        } else {
            statement += std::to_string(t.incorrectQuestions[i]->second);
        }
        statement += " = ";
        statement += t.incorrectQuestions[i]->reason + "\n";
        std::cout << statement;
        outf << statement;
    }

    outf << "---------------------------------------";    
    
    outf.close();
}