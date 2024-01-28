#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using NetworkMap = std::map<std::string,
    std::pair<std::string, std::string>, std::less<>>;

long long walk(const NetworkMap& network, std::vector<std::string>& nodes,
               std::string instruction, bool part_2 = false) {
  std::vector<int> step_counts{};
  for (auto& node: nodes) {
    long long step_count{0};
    while (true) {
      if ((part_2 && node[2] == 'Z') || (node == "ZZZ")) {
        break;
      }

      if (instruction[step_count % instruction.size()] == 'L') {
        node = network.at(node).first;
      } else {
        node = network.at(node).second;
      }
      ++step_count;
    }
    step_counts.emplace_back(step_count);
  }

  if (part_2) {
    long long lcm{1};
    for (auto step_count: step_counts) {
      lcm = std::lcm(lcm, step_count);
    }
    return lcm;
  } else {
    return step_counts[0];
  }
}

int main() {
  std::string instruction;
  std::getline(std::cin, instruction);

  NetworkMap network{};
  std::vector<std::string> ending_a_nodes{};
  std::string line{};
  std::getline(std::cin, line);
  while (std::getline(std::cin, line)) {
    network[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
    if (line.substr(2, 1) == "A") {
      ending_a_nodes.emplace_back(line.substr(0, 3));
    }
  }
  std::vector<std::string> first_node{network.begin()->first};
  std::cout << "Human step count: "
            << walk(network, first_node, instruction) << '\n';
  std::cout << "Ghost step count: "
            << walk(network, ending_a_nodes, instruction, true) << '\n';
}