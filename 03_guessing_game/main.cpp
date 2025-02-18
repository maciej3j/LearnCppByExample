#include <iostream>
#include <limits>

unsigned int some_const_number(){
    return 42;
}

unsigned input() {
    unsigned number;
    while (!(std::cin >> number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a number.\n>";
    }
    return number;
}

void guess_number(unsigned number) {
    std::cout << "Guess the number.\n";
    unsigned guess = input();
    while (guess != number) {
        std::cout << guess << " is wrong. Try again\n";
        guess = input();
    }
    std::cout << "Well done.\n";
}

int main() {
    guess_number(some_const_number());
}