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
            numRanges[0] = 0;
            numRanges[1] = 12;
            numRanges[2] = 0;
            numRanges[3] = 12;
            break;
        case 2:
            difficulty = Level::Two;
            numRanges[0] = 0;
            numRanges[1] = 20;
            numRanges[2] = 0;
            numRanges[3] = 20;
            break;
        case 3: 
            difficulty = Level::Three;
            numRanges[0] = 10;
            numRanges[1] = 20;
            numRanges[2] = 10;
            numRanges[3] = 20;
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
            first_num = numGen.generate(numRanges[0], numRanges[1]);
            second_num = numGen.generate(numRanges[2], numRanges[3]);
            break;
        case '-':
            first_num = numGen.generate(numRanges[0], numRanges[1]);
            second_num = numGen.generate(numRanges[2], first_num);
            break;
        case '/':
            int temp = numGen.generate(numRanges[0] > 0 ? numRanges[0] : 1, numRanges[1]);
            second_num = numGen.generate(numRanges[2] > 0 ? numRanges[2] : 1, numRanges[3]);
            first_num = temp * second_num;
            break;
    }
    currentQuestion = std::make_unique<Question>(first_num, second_num, operation);
}

void Test::askQuestion() {
    if (currentQuestion->operation == 'r') {
        std::cout << "sqrt(" << currentQuestion->first << ") = ";
    } else {
        std::cout << currentQuestion->first << " " << currentQuestion->operation << " " << currentQuestion->second << " = ";
    }
}

void Test::printIncorrectQuestions() {
    std::cout << "Incorrect Questions:\n";
    for (int i = 0; i < incorrectQuestions.size(); i++) {
        std::cout << i + 1 << ") " << incorrectQuestions[i]->first << " x " << incorrectQuestions[i]->second << " = " << incorrectQuestions[i]->reason << "\n";
    }
}

void Test::setCustomRange() {
    std::cout << "Enter new range: ";
    std::cin >> numRanges[0] >> numRanges[1] >> numRanges[2] >> numRanges[3];
}