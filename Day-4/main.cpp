#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
  ifstream input("input.txt");
  long sum = 0;

  string line;
  while (getline(input, line)) {
    line = line.substr(10);

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
          card = (card == 0) ? 1 : card*2;
        }
        n = 0;
      }
    }

    if (n != 0) {
      if (winning_numbers.count(n) > 0) {
        card = (card == 0) ? 1 : card*2;
      }
      n = 0;
    }

    sum += card;
  }
  cout << sum << "\n";

  return 0;
}
