#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
  ifstream input("input.txt");
  long long sum = 0;

  map<int, long long> num_cards;

  int card_idx;
  string line;
  while (getline(input, line)) {
    line = line.substr(10);

    card_idx++;
    long n = 0;

    set<long> winning_numbers;
    for (char& ch : line) {
      if (isdigit(ch)) n = n*10 + (ch - '0');
      else if (ch == '|') break;
      else if (n != 0) {
        winning_numbers.insert(n);
        n = 0;
      }
    }

    auto pipe_loc = line.find('|');
    line = line.substr(pipe_loc+2);

    long card = 0;
    for (char& ch : line) {
      if (isdigit(ch)) n = n*10 + (ch - '0');
      else if (n != 0) {
        if (winning_numbers.count(n) > 0) {
          card++;
        }
        n = 0;
      }
    }

    if (n != 0) {
      if (winning_numbers.count(n) > 0) {
        card++;
      }
      n = 0;
    }

    if (num_cards[card_idx] == 0) num_cards[card_idx] = 1;
    for (int i = card_idx+1; i <= card_idx+card; i++) {
      if (num_cards[i] == 0) num_cards[i] = 1;
      num_cards[i] += num_cards[card_idx];
    }
  }

  for (auto &num : num_cards) {
    sum += num.second;
  }
  cout << sum << "\n";

  return 0;
}
