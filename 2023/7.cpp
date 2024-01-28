#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class TYPE {
  HIGH_CARD,
  ONE_PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  FIVE_OF_A_KIND,
};

int rankCard(char card, bool part_2) {
  switch (card) {
    case 'A':
      return 14;
    case 'K':
      return 13;
    case 'Q':
      return 12;
    case 'J':
      return part_2 ? 1 : 11;
    case 'T':
      return 10;
    default:
      return card - '0';
  }
}

TYPE getType(std::string_view hand, bool part_2) {
  std::vector<int> count_total(15, 0);
  for (int i{0}; i < hand.size(); ++i) {
    if (part_2 && hand[i] == 'J') {
      continue;
    }
    ++count_total[rankCard(hand[i], part_2)];
  }

  auto max_element{std::max_element(count_total.begin(), count_total.end())};
  if (part_2) {
    int j_count{static_cast<int>(std::count(hand.begin(), hand.end(), 'J'))};
    *max_element += j_count;
  }
  long long max{*max_element};
  if (max == 5) {
    return TYPE::FIVE_OF_A_KIND;
  } else if (max == 4) {
    return TYPE::FOUR_OF_A_KIND;
  } else if (max == 3) {
    if (std::count(count_total.begin(), count_total.end(), 2) >= 1) {
      return TYPE::FULL_HOUSE;
    } else {
      return TYPE::THREE_OF_A_KIND;
    }
  } else if (max == 2) {
    if (std::count(count_total.begin(), count_total.end(), 2) >= 2) {
      return TYPE::TWO_PAIR;
    } else {
      return TYPE::ONE_PAIR;
    }
  } else {
    return TYPE::HIGH_CARD;
  }
}

class CamelSort {
public:
  explicit CamelSort(bool part_2) : part_2{part_2} {};

  bool operator()(const std::pair<std::string, long long>& a,
                  const std::pair<std::string, long long>& b) const {
    std::string first_deck{a.first};
    std::string second_deck{b.first};
    TYPE first_type{getType(first_deck, part_2)};
    TYPE second_type{getType(second_deck, part_2)};
    if (first_type != second_type) {
      return first_type < second_type;
    } else {
      for (int i{0}; i < first_deck.size(); ++i) {
        if (first_deck[i] != second_deck[i]) {
          return rankCard(first_deck[i], part_2)
                 < rankCard(second_deck[i], part_2);
        }
      }
      return true;
    }
  }

private:
  bool part_2;
};

int main() {
  std::vector<std::pair<std::string, long long>> camel_cards{};
  std::string line{};
  while (std::getline(std::cin, line)) {
    std::istringstream iss{line};
    std::string deck{};
    iss >> deck;
    long long bid{};
    iss >> bid;
    camel_cards.emplace_back(deck, bid);
  }

  std::sort(camel_cards.begin(), camel_cards.end(), CamelSort(false));
  long long bid_total{0};
  for (int i{0}; i < camel_cards.size(); ++i) {
    bid_total += camel_cards[i].second * (i + 1);
  }
  std::cout << "Part 1: " << bid_total << '\n';
  std::sort(camel_cards.begin(), camel_cards.end(), CamelSort(true));
  bid_total = 0;
  for (int i{0}; i < camel_cards.size(); ++i) {
    bid_total += camel_cards[i].second * (i + 1);
  }
  std::cout << "Part 2: " << bid_total << '\n';

  return 0;
}