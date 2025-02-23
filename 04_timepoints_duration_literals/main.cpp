#include <iostream>
#include <chrono>

// what compiler says in cppinsights
// std::chrono::time_point<std::chrono::system_clock,
// std::chrono::duration<long, std::ratio<86400, 1> > >
// event = std::chrono::time_point<std::chrono::system_clock,
// std::chrono::duration<long, std::ratio<86400, 1> > >
// (new_years_eve.operator time_point());
// std::chrono::duration<long, std::ratio<1, 1000000000> > dur =
// std::chrono::operator-(event, now);

void duration_to_end_of_year() {
    std::chrono::time_point now = std::chrono::system_clock::now();
    constexpr auto year = 2025;
    auto new_years_eve = std::chrono::year_month_day(
        std::chrono::year(year),
        std::chrono::month(12),
        std::chrono::day(31));
    auto event = std::chrono::sys_days(new_years_eve);
    std::chrono::duration dur = event - now;
    std::cout << dur << " until event\n";
}

void durations(){
    using namespace std::chrono;
    using centuries = duration<long long, std::ratio_multiply<years::period, std::hecto>>;
    centuries two_hundred_years = centuries(2);
    seconds sec = two_hundred_years;
    hours hrs = two_hundred_years;
    days  day_count = duration_cast<days>(two_hundred_years);
    std::cout << "Two centuries is approximately " << day_count << '\n';
}

template <typename T>
concept Quacks = requires (T t){ t.Quack(); };

template<typename T>
requires Quacks<T>
void might_be_a_duck(T x) {x.Quack();}

void also_must_be_a_duck(Quacks auto x) {
    x.Quack();
}

int main(){
    // duration_to_end_of_year();
    might_be_a_duck(42);
}
