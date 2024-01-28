#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

std::pair<int, int> getCard(std::string_view card) {
  std::vector<int> winning_numbers{};
  std::vector<int> card_numbers{};

  std::istringstream iss{card.data()};
  std::string token{};
  iss >> token;
  iss >> token; // Ignore game id information
  bool in_winning_numbers{true};
  while (iss >> token) {
    if (std::isdigit(token[0])) {
      if (in_winning_numbers) {
        winning_numbers.push_back(std::stoi(token));
      } else {
        card_numbers.push_back(std::stoi(token));
      }
    } else {
      in_winning_numbers = false;
    }
  }
  std::sort(winning_numbers.begin(), winning_numbers.end());
  std::sort(card_numbers.begin(), card_numbers.end());
  std::vector<int> won_numbers{};
  std::set_intersection(winning_numbers.begin(), winning_numbers.end(),
                        card_numbers.begin(), card_numbers.end(),
                        std::back_inserter(won_numbers));
  return {static_cast<int>(std::pow(2,
                                    static_cast<int>(won_numbers.size()) - 1)),
          won_numbers.size()};
}

int main() {
  int point_total{0};
  int card_id{0};
  std::vector<int> card_count;
  std::string line{};
  while (std::getline(std::cin, line)) {
    auto [points, won_number_count]{getCard(line)};
    point_total += points;
    if (card_count.size() < card_id + 1) {
      card_count.emplace_back(1);
    } else {
      card_count[card_id] += 1;
    }

    for (int i{1}; i <= won_number_count; ++i) {
      if (card_count.size() < card_id + i + 1) {
        card_count.emplace_back(card_count[card_id]);
      } else {
        card_count[card_id + i] += card_count[card_id];
      }
    }

    ++card_id;
  }

  int card_count_total{std::accumulate(card_count.begin(),
                                       card_count.end(), 0)};
  std::cout << "Card count total: " << card_count_total << '\n';
  std::cout << "Point total: " << point_total << '\n';
}
