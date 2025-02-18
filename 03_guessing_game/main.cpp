#include <iostream>
#include <limits>
#include <random>
#include <optional>
#include <functional>
#include <format>
#include <concepts>

auto some_random_number(){
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int>dist(1, 100);
    return dist(engine);
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

template <typename T, typename P>
class Map{
public:
    T m_key;
    P m_value;
    Map(T new_key, P new_value)
        : m_key{new_key}, m_value{new_value} {}
};


std::function<std::string(int, int)> callable = [](int number, int guess) {
    return std::format("Your guess was too {}\n", (guess < number ? "small" : "big"));
};

std::optional<int> read_number(std::istream& in) {
    int result{};
    if (in >> result) {
        return result;
    }
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return {};
}

void guess_number_with_clues(unsigned number, std::invocable<int, int> auto message) {
    std::cout << "Guess the number.\n";
    std::optional<int> guess;
    while ((guess = read_number(std::cin))) {
        if (guess.value() == number) {
            std::cout << "Well done.\n";
            return;
        }
        std::cout << message(number, guess.value());
        std::cout << '>';
    }
    std::cout << "The number was " << number << "\n";

}

int main() {
    // auto make_message = [](int number, int guess) {
    //     return std::format("Your guess was too {}\n",  (guess < number ? "small" : "big"));
    // };
    // guess_number_with_clues(some_random_number(), make_message);
    Map map1(111222,std::string{"Steve Murphy"});
    std::cout << "key : " << map1.m_key << std::endl;
    std::cout << "value : " << map1.m_value << std::endl;
}