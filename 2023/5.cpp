#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void mapElements(
    std::vector<long long>& elements,
    const std::vector<std::vector<long long>>& map, bool ranges = false) {
  if (ranges) {
    std::vector<long long> new_elements{};
    for (int i{0}; i < static_cast<int>(elements.size()) - 1; i += 2) {
      bool mapped{false};
      for (auto mapping: map) {
        // Begin and end inclusive
        long long begin_range{elements[i]};
        long long end_range{elements[i] + elements[i + 1] - 1};
        long long begin_mapping{mapping[1]};
        long long end_mapping{mapping[1] + mapping[2] - 1};
        long long overlap_begin{std::max(begin_range, begin_mapping)};
        long long overlap_end{std::min(end_range, end_mapping)};

        if (overlap_begin <= overlap_end) {
          mapped = true;
          new_elements.emplace_back(overlap_begin + mapping[0] - mapping[1]);
          new_elements.emplace_back(overlap_end - overlap_begin + 1);

          if (begin_range < begin_mapping) {
            elements.emplace_back(begin_range);
            elements.emplace_back(begin_mapping - begin_range);
          }

          if (end_range > end_mapping) {
            elements.emplace_back(end_mapping + 1);
            elements.emplace_back(end_range - end_mapping);
          }
          break;
        }
      }
      if (!mapped) {
        new_elements.emplace_back(elements[i]);
        new_elements.emplace_back(elements[i + 1]);
      }
    }
    elements = new_elements;
  } else {
    for (int i{0}; i < elements.size(); ++i) {
      for (auto mapping: map) {
        if (mapping[1] <= elements[i]
            && elements[i] < mapping[1] + mapping[2]) {
          elements[i] += mapping[0] - mapping[1];
          break;
        }
      }
    }
  }
}


int main() {
  std::string line{};
  std::getline(std::cin, line);

  std::istringstream iss{line};
  std::string symbol{};
  iss >> symbol;
  std::vector<long long> elements{};
  std::vector<long long> ranges{};
  while (iss >> symbol) {
    elements.emplace_back(std::stoll(symbol));
  }
  ranges = elements;
  std::getline(std::cin, line);
  std::getline(std::cin, line);

  std::vector<std::vector<long long>> map{};
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      mapElements(elements, map);
      mapElements(ranges, map, true);
      map = std::vector<std::vector<long long>>{};
      std::getline(std::cin, line);
    } else {
      std::vector<long long> row{};
      iss = std::istringstream{line};
      while (iss >> symbol) {
        row.emplace_back(std::stoll(symbol));
      }
      map.emplace_back(row);
    }
  }
  mapElements(elements, map);
  mapElements(ranges, map, true);

  std::vector<long long> values{};
  for (int i{0}; i < ranges.size() - 1; i += 2) {
    values.emplace_back(ranges[i]);
  }
  std::cout << "Minimum distance (part 1): "
            << *std::min_element(elements.begin(), elements.end()) << '\n';
  std::cout << "Minimum distance (part 2): "
            << *std::min_element(values.begin(), values.end()) << '\n';
  return 0;
}
