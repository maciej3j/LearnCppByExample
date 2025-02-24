
#include <iostream>
#include <chrono>
#include <thread>
#include <string>


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

void payday(){
  using namespace std::chrono;

  time_point now = system_clock::now();
  const auto ymd = year_month_day{floor<days>(now)};

  auto pay_day = ymd.year() / ymd.month() / Friday[last];
  auto event = sys_days(pay_day);
  duration dur = event - now;
  std::cout << duration_cast<days>(dur) << " until pay_day\n";
}

constexpr std::chrono::system_clock::duration countdown(std::chrono::system_clock::time_point start){
  using namespace std::chrono;

  auto days_only = floor<days>(start);
  const auto ymd = year_month_day(days_only);
  auto this_year = ymd.year();
  auto new_years_eve = this_year / December / last;

  auto event = sys_days(new_years_eve);
  return event - start;
}

void check_properties(){
  using namespace std::chrono;
  constexpr auto new_years_eve = 2022y / December / last;
  constexpr auto one_day_away = sys_days{new_years_eve } - 24h;
  constexpr auto result = countdown(one_day_away);
  static_assert(duration_cast<days>(result) == days{1});
}

std::optional<std::chrono::year_month_day> read_date(std::istream& in){
  using namespace std::string_literals;

  auto format_str = "%Y-%m-%d"s;
  std::chrono::year_month_day date;
  if (in >> std::chrono::parse(format_str, date)){ // is the input valid?
    return date;
  }
  in.clear(); // clears invalid input
  std::cout << "Invalid format. Expected " << format_str << "\n";
  return {}; // return optional with no value
}

int main(){
  // countdown();
  // payday();
  check_properties();

  using namespace std::chrono;
  year_month_day date;
  std::cin >> parse("%Y-%m-%d", date);


  for(int i{}; i < 5; i++){
    std::this_thread::sleep_for(5000ms);
    auto dur = countdown(system_clock::now());
    std::cout << duration_cast<seconds>(dur) << " until event\n";
  }
}
