#include <fstream>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
  ifstream input("input.txt");
  long sum_total = 0;
  long sum_not_part = 0;

  regex rgx("([0-9]+)");
  regex rgx_symb(R"([^\d\.])");

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
      sum_total += num;

      bool is_part = false;

      if (num_start-1 >= 0 && regex_match(cur_line.substr(num_start-1, 1), rgx_symb)) {
        is_part = true;
      }

      if (num_end < cur_line.size() && regex_match(cur_line.substr(num_end, 1), rgx_symb)) {
        is_part = true;
      }

      if (!prev_line.empty()) {
        for (auto i = num_start-1; i <= num_end; i++) {
          if (i-1 >= 0 && i < prev_line.size() && regex_match(prev_line.substr(i, 1), rgx_symb)) {
            is_part = true;
            break;
          }
        }
      }
      
      if (!next_line.empty()) {
        for (auto i = num_start-1; i <= num_end; i++) {
          if (i-1 >= 0 && i < next_line.size() && regex_match(next_line.substr(i, 1), rgx_symb)) {
            is_part = true;
            break;
          }
        }
      }

      if (!is_part) sum_not_part += num;

      rgx_start = rgx_match.suffix().first;
    }

    prev_line = cur_line;
    cur_line = next_line;
  }

  cout << sum_total - sum_not_part << "\n";

  return 0;
}
