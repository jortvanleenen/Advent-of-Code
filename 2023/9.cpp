#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>

bool allZero(const std::deque<long long>& measurements) {
  return std::all_of(measurements.begin(), measurements.end(),
                     [](long long ll) { return ll == 0; });
}

long long getValue(const std::deque<long long>& measurements,
                   bool part_2 = false) {
  std::deque <std::deque<long long>> differences{};
  differences.emplace_back(measurements);
  while (!allZero(differences.back())) {
    std::deque<long long> difference{};
    for (int i{0}; i < differences.back().size() - 1; ++i) {
      difference.emplace_back(differences.back()[i + 1] -
                              differences.back()[i]);

    }
    differences.emplace_back(difference);
  }
  if (part_2) {
    for (int i{static_cast<int>(differences.size()) - 1}; i > 0; --i) {
      differences[i - 1].emplace_front(differences[i - 1].front() -
                                      differences[i].front());
    }
  } else {
    for (int i{static_cast<int>(differences.size()) - 1}; i > 0; --i) {
      differences[i - 1].emplace_back(differences[i - 1].back() +
                                      differences[i].back());
    }
  }
  return part_2 ? differences[0].front() : differences[0].back();
}

int main() {
  long long next_value_total{0};
  long long previous_value_total{0};
  std::string line{};
  while (std::getline(std::cin, line)) {
    std::istringstream iss{line};
    std::deque<long long> measurements{};
    long long measurement{};
    while (iss >> measurement) {
      measurements.emplace_back(measurement);
    }
    next_value_total += getValue(measurements);
    previous_value_total += getValue(measurements, true);
  }

  std::cout << "Prediction total: " << next_value_total << '\n';
  std::cout << "History total: " << previous_value_total << '\n';
  return 0;
}