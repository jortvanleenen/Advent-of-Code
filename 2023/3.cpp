#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

bool isSymbol(char character) {
  return !(std::isdigit(character) || character == '.' || character == '\r');
}

bool isGear(char character) {
  return character == '*';
}

int consumePart(std::vector<std::string>& engine, int row,
                int column) {
  while (std::isdigit(engine[row][column])) {
    --column;
  }
  ++column;
  int part_number{0};
  while (std::isdigit(engine[row][column])) {
    part_number = part_number * 10 + (engine[row][column] - '0');
    engine[row][column] = '.';
    ++column;
  }
  return part_number;
}

std::pair<long long, long long> getNeighbouringParts(
    std::vector<std::string>& engine, int row, int column) {
  std::vector<int> part_numbers{};
  for (int i{-1}; i <= 1; ++i) {
    for (int j{-1}; j <= 1; ++j) {
      int part_row{row + i};
      int part_column{column + j};
      if (part_row >= 0 && part_row < engine.size()
          && part_column >= 0 && part_column < engine[part_row].size()
          && std::isdigit(engine[part_row][part_column])) {
        part_numbers.emplace_back(
            consumePart(engine, part_row, part_column));
      }
    }
  }

  long long part_number_total{0};
  part_number_total = std::accumulate(
      part_numbers.begin(), part_numbers.end(), part_number_total);
  long long gear_ratio{0};
  if (part_numbers.size() == 2 && isGear(engine[row][column])) {
    gear_ratio = part_numbers[0] * part_numbers[1];
  }

  return {part_number_total, gear_ratio};
}

int main() {
  std::string line{};
  std::vector<std::string> engine{};
  while (std::getline(std::cin, line)) {
    engine.emplace_back(line);
  }

  long long sum_part_numbers{0};
  long long sum_gear_ratios{0};
  for (int row{0}; row < engine.size(); ++row) {
    for (int column{0}; column < engine[row].size(); ++column) {
      if (isSymbol(engine[row][column])) {
        auto [sum_neighbouring_part_numbers, gear_ratio]{
            getNeighbouringParts(engine, row, column)};
        sum_part_numbers += sum_neighbouring_part_numbers;
        sum_gear_ratios += gear_ratio;
      }
    }
  }
  std::cout << "Sum of part numbers: " << sum_part_numbers << '\n';
  std::cout << "Sum of gear ratios: " << sum_gear_ratios << '\n';

  return 0;
}
