#include <fstream>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
  ifstream input("input.txt");
  long sum = 0;

  string line;
  long game_idx = 0;
  while (getline(input, line)) {
    game_idx++;

    long blues = 0;
    long reds = 0;
    long greens = 0;
    
    regex rgx("([0-9]+) (blue|red|green)");
    smatch rgx_match;
    auto rgx_start(line.cbegin());
    bool is_possible = true;
    while (regex_search(rgx_start, line.cend(), rgx_match, rgx)) {
      if (rgx_match[2].str() == "red" && stol(rgx_match[1].str()) > 12) is_possible = false; //reds += stol(rgx_match[1].str());
      if (rgx_match[2].str() == "green" && stol(rgx_match[1].str()) > 13) is_possible = false; //greens += stol(rgx_match[1].str());
      if (rgx_match[2].str() == "blue" && stol(rgx_match[1].str()) > 14) is_possible = false; //blues += stol(rgx_match[1].str());
      
      if (!is_possible) break;
      rgx_start = rgx_match.suffix().first;
    };
    
    if (is_possible) sum += game_idx;
  }
  cout << sum;
}
