#include <iostream>
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <utility>

std::pair<bool, int> validGame(std::string_view line) {
  static std::map<std::string, int, std::less<>> bag_content{
      {"red",   12},
      {"green", 13},
      {"blue",  14}
  };

  std::istringstream iss{line.data()};
  std::string partial{};
  iss >> partial;
  iss >> partial;
  int game_id{std::stoi(partial)};
  while (iss >> partial) {
    int amount{std::stoi(partial)};
    iss >> partial;
    if (bag_content.at(partial) < amount) {
      return {false, game_id};
    }
  }
  return {true, game_id};
}

int main() {
  std::string line{};
  int game_id_total{0};
  while (std::getline(std::cin, line)) {
    // Line is e.g. 'Game 7: 3 blue, 1 red; 3 blue, 10 green; 4 green, 5 blue'
    line.erase(
        std::remove_if(line.begin(),
                       line.end(),
                       [](char x) { return (x == ':' || x == ',' || x == ';'); }
        ), line.end());
    auto [valid, game_id] {validGame(line)};
    if (valid) {
      game_id_total += game_id;
    }
  }
  std::cout << game_id_total << '\n';
  return 0;
}
