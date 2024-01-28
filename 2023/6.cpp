#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int numberOfWins(long long time, long long distance) {
  int wins{0};
  bool found_winning_way{false};
  for (int i{0}; i < time; ++i) {
    if ((time - i) * i > distance) {
      wins += 1;
      found_winning_way = true;
    } else if (found_winning_way) {
      break;
    }
  }

  return wins;
}

int main() {
  std::string line{};
  std::string symbol{};
  std::getline(std::cin, line);
  std::istringstream iss{line};
  std::vector<long long> times{};
  std::string time{};
  while (iss >> symbol) {
    if (std::isdigit(symbol[0])) {
      times.emplace_back(std::stoll(symbol));
      time.append(symbol);
    }
  }
  std::getline(std::cin, line);
  iss = std::istringstream{line};
  std::vector<long long> distances{};
  std::string distance{};
  while (iss >> symbol) {
    if (std::isdigit(symbol[0])) {
      distances.emplace_back(std::stoll(symbol));
      distance.append(symbol);
    }
  }

  std::vector<int> total_wins{};
  for (int i{0}; i < times.size(); ++i) {
    total_wins.emplace_back(numberOfWins(times[i], distances[i]));
  }
  int single_race_wins{numberOfWins(std::stoll(time), std::stoll(distance))};
  std::cout << "Multiplication winning ways: "
            << std::accumulate(total_wins.begin(), total_wins.end(), 1,
                               std::multiplies<>()) << '\n';
  std::cout << "Single race winning ways: " << single_race_wins << '\n';
  return 0;
}
