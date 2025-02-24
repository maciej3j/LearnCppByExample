#include <iostream>
#include <chrono>


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

void countdown(){
  using namespace std::chrono;
  time_point now = system_clock::now();
  const auto ymd = year_month_day{floor<days>(now)};
  auto this_year = ymd.year();auto new_years_eve = this_year / December / 31;
  auto event = sys_days(new_years_eve);
  duration dur = event - now;
  std::cout << duration_cast<days>(dur) << " until event \n";
}

int main(){
  countdown();
}
