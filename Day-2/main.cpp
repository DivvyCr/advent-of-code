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

    long max_blues = 0;
    long max_reds = 0;
    long max_greens = 0;
    
    regex rgx("([0-9]+) (blue|red|green)");
    smatch rgx_match;
    auto rgx_start(line.cbegin());
    while (regex_search(rgx_start, line.cend(), rgx_match, rgx)) {
      if (rgx_match[2].str() == "red") {
        long reds = stol(rgx_match[1].str());
        max_reds = reds > max_reds ? reds : max_reds;
      }
      if (rgx_match[2].str() == "green") {
        long greens = stol(rgx_match[1].str());
        max_greens = greens > max_greens ? greens : max_greens;
      }
      if (rgx_match[2].str() == "blue") {
        long blues = stol(rgx_match[1].str());
        max_blues = blues > max_blues ? blues : max_blues;
      }
      
      rgx_start = rgx_match.suffix().first;
    };
    
    sum += max_reds*max_greens*max_blues;
  }
  cout << sum;
}
