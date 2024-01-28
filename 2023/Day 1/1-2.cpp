#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
  const std::vector<std::string> values{
      "zero",
      "one",
      "two",
      "three",
      "four",
      "five",
      "six",
      "seven",
      "eight",
      "nine",
      "0",
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8",
      "9"
  };

  int accumulator{0};
  std::string line{};
  while (std::getline(std::cin, line)) {
    int current_value{0};

    std::size_t index{std::numeric_limits<std::size_t>::max()};
    for (int i{0}; i < values.size(); ++i) {
      std::size_t current_index{line.find(values[i])};
      if (current_index != std::string::npos && current_index < index) {
        index = current_index;
        current_value = i;
      }
    }
    int first{std::isdigit(values[current_value][0]) ?
              values[current_value][0] - '0' : current_value};

    index = 0;
    for (int i{0}; i < values.size(); ++i) {
      std::size_t current_index{line.rfind(values[i])};
      if (current_index != std::string::npos && current_index >= index) {
        index = current_index;
        current_value = i;
      }
    }
    int last{std::isdigit(values[current_value][0]) ?
             values[current_value][0] - '0' : current_value};

    accumulator += first * 10 + last;
  }
  std::cout << accumulator << '\n';
  return 0;
}
