#include <iostream>
#include <string>

int main() {
  std::string line{};
  int accumulator{0};
  while (std::getline(std::cin, line)) {
    int value{0};
    for (int i{0}; i < line.size(); ++i) {
      if (std::isdigit(line[i])) {
        value = line[i] - '0';
        break;
      }
    }

    for (int i{static_cast<int>(line.size() - 1)}; i >= 0; --i) {
      if (std::isdigit(line[i])) {
        value = value * 10 + line[i] - '0';
        break;
      }
    }
    accumulator += value;
  }
  std::cout << accumulator << '\n';
  return 0;
}
