#include <iostream>
#include <functional>
#include <limits>
#include <map>
#include <numeric>
#include <sstream>
#include <string>

int setPower(std::string_view line) {
  std::map<std::string, int, std::less<>> minima{
      {"red",   std::numeric_limits<int>::min()},
      {"blue",  std::numeric_limits<int>::min()},
      {"green", std::numeric_limits<int>::min()},
  };
  std::istringstream iss{line.data()};
  std::string partial{};
  iss >> partial;
  iss >> partial;
  while (iss >> partial) {
    int amount{std::stoi(partial)};
    iss >> partial;
    if (minima.at(partial) < amount) {
      minima[partial] = amount;
    }
  }
  int set_power{1};
  for (const auto& [type, minimum] : minima) {
    set_power *= minimum;
  }
  return set_power;
}

int main() {
  std::string line{};
  int sum_set_power{0};
  while (std::getline(std::cin, line)) {
    // Line is e.g. 'Game 7: 3 blue, 1 red; 3 blue, 10 green; 4 green, 5 blue'
    line.erase(
        std::remove_if(line.begin(),
                       line.end(),
                       [](char x) { return (x == ':' || x == ',' || x == ';'); }
        ), line.end());
    sum_set_power += setPower(line);
  }
  std::cout << sum_set_power << '\n';
  return 0;
}
