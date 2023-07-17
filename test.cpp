#include "test.hpp"

Test::Test(std::string operations, std::string student_name) {
    student = student_name;
    for (char c: operations) {
        switch(c) {
            case 'a':
                possibleOperations += "+";
                break;
            case 'd':
                possibleOperations += "/";
                break;
            case 's':
                possibleOperations += '-';
                break;
            case 'm':
                possibleOperations += "x";
        }
    }
}

void Test::makeNewQuestion() {
    char operation = possibleOperations.size() == 1 ? possibleOperations[0]: possibleOperations[numGen.generate(0, possibleOperations.size() - 1)];
    int first_num;
    int second_num;
    switch (operation) {
        case '+':
        case '*':
            first_num = numGen.generate();
            second_num = numGen.generate();
            break;
        case '-':
            first_num = numGen.generate(0,10);
            second_num = numGen.generate(0, first_num);
            break;
        case '/':
            int temp = numGen.generate();
            second_num = numGen.generate();
            first_num = temp * second_num;
            break;
    }
    currentQuestion = std::make_unique<Question>(first_num, second_num, operation);
}

void Test::askQuestion() {
    std::cout << currentQuestion->first << " " << currentQuestion->operation << " " << currentQuestion->second << " = ";
}

void Test::printIncorrectQuestions() {
    std::cout << "Incorrect Questions:\n";
    for (int i = 0; i < incorrectQuestions.size(); i++) {
        std::cout << i + 1 << ") " << incorrectQuestions[i]->first << " x " << incorrectQuestions[i]->second << " = " << incorrectQuestions[i]->reason << "\n";
    }
}