#include <iostream>
#include <limits>
#include <random>
#include <optional>
#include <functional>
#include <format>
#include <concepts>
#include <vector>

constexpr bool is_prime(const int n) {
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i{5}; i*i < n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

auto some_prime_number(){
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int>dist(1, 99999);
    int n{};
    while (!is_prime(n)) {
        n = dist(engine);
    }
    return n;
}

std::string check_which_digits_correct(int number, int guess) {
    auto ns = std::format("{:0>5}", (number));
    auto gs = std::format("{:0>5}", (guess));
    std::string matches(5, '.');
    for (size_t i = 0, stop = gs.length(); i < stop; ++i) {
        char guess_char = gs[i];
        if (i < ns.length() && guess_char == ns[i]) {
            matches[i] = '*';
            ns[i] = '*';
        }
    }
    for (size_t i = 0, stop = gs.length(); i < stop; i++) {
        char guess_char = gs[i];
        if (i < ns.length() && matches[i] != '*') {
            if (size_t idx = ns.find(guess_char, 0); idx != std::string::npos) {
                matches[i] = '^';
                ns[idx] = '^';
            }
        }
    }
    return matches;
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

void guess_number_with_more_clues(unsigned number, auto messages) {
    std::cout << "Guess the number.\n";
    std::optional<int> guess;
    while ((guess = read_number(std::cin))) {
        if (guess.value() == number) {
            std::cout << "Well done.\n";
            return;
        }
        std::cout << std::format("{:0>5} is wrong. Try again\n", guess.value());
        for (auto message : messages) {
            auto clue = message(guess.value());
            if (clue.length()) {
                std::cout << clue;
                break;
            }
        }
    }

    std::cout << std::format("The number was {:0>5}\n", (number));

}

constexpr void check_properties() {
    static_assert(is_prime(2));
}

int main() {
    check_properties();
    auto check_prime = [](int guess) {
        return std::string((is_prime(guess)) ? "" : "Not prime\n");
    };
    auto check_length = [](int guess) {
        return std::string((guess < 100000) ? "" : "Too long\n");
    };
    const int number = some_prime_number();
    auto check_digits = [number](int guess) {
        return std::format("{}\n", check_which_digits_correct(number, guess));
    };
    std::vector<std::function<std::string(int)>>messages{check_length, check_prime, check_digits};

    guess_number_with_more_clues(some_prime_number(), messages);

}