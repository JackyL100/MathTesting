#include "test.hpp"

Test::Test(std::string operations, std::string student_name, int level) {
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
    switch (level) {
        case 1:
            difficulty = Level::One;
            min = 0;
            max = 12;
            break;
        case 2:
            difficulty = Level::Two;
            min = 0;
            max = 20;
            break;
        case 3: 
            difficulty = Level::Three;
            min = 10;
            max = 20;
            break;
    }
}

void Test::makeNewQuestion() {
    char operation = possibleOperations.size() == 1 ? possibleOperations[0]: possibleOperations[numGen.generate(0, possibleOperations.size() - 1)];
    int first_num;
    int second_num;

    switch (operation) {
        case '+':
        case 'x':
            first_num = numGen.generate(min, max);
            second_num = numGen.generate(min, max);
            break;
        case '-':
            first_num = numGen.generate(min, max);
            second_num = numGen.generate(min, first_num);
            break;
        case '/':
            int temp = numGen.generate(min > 0 ? min : 1, max);
            second_num = numGen.generate(min > 0 ? min : 1, max);
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