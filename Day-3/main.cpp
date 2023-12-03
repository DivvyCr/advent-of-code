#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;

std::map<std::pair<int, int>, std::vector<int>> gears;

int main() {
  ifstream input("input.txt");
  long sum = 0;

  regex rgx("([0-9]+)");
  regex rgx_symb(R"([^\d\.])");

  int cur_idx = 0;
  string prev_line;
  string cur_line;
  string next_line;

  getline(input, cur_line);
  while (!cur_line.empty()) {
    getline(input, next_line);
    smatch rgx_match;
    auto rgx_start = cur_line.cbegin();
    while (regex_search(rgx_start, cur_line.cend(), rgx_match, rgx)) {
      int num_start = std::distance(cur_line.cbegin(), rgx_start) + rgx_match.position(1);
      int num_end = num_start + rgx_match.length();
      long num = stol(cur_line.substr(num_start, rgx_match.length()));

      if (num_start-1 >= 0 && cur_line[num_start-1] == '*') {
        /* cout << num_start-1 << ", " << cur_idx << "\n"; */
        gears[std::make_pair(num_start-1, cur_idx)].push_back(num);
      }

      if (num_end < cur_line.size() && cur_line[num_end] == '*') {
        /* cout << num_end << ", " << cur_idx << "\n"; */
        gears[std::make_pair(num_end, cur_idx)].push_back(num);
      }

      if (!prev_line.empty()) {
        for (auto i = num_start-1; i <= num_end; i++) {
          if (i >= 0 && i < prev_line.size() && prev_line[i] == '*') {
            /* cout << i << ", " << cur_idx-1 << "\n"; */
            gears[std::make_pair(i, cur_idx-1)].push_back(num);
          }
        }
      }

      if (!next_line.empty()) {
        for (auto i = num_start-1; i <= num_end; i++) {
          if (i >= 0 && i < next_line.size() && next_line[i] == '*') {
            /* cout << i << ", " << cur_idx+1 << "\n"; */
            gears[std::make_pair(i, cur_idx+1)].push_back(num);
          }
        }
      }

      rgx_start = rgx_match.suffix().first;
    }

    prev_line = cur_line;
    cur_line = next_line;
    cur_idx++;
  }

  for (auto &gear : gears) {
    if (gear.second.size() == 2) sum += gear.second[0]*gear.second[1];
  }
  cout << sum << "\n";

  return 0;
}
