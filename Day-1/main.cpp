#include <fstream>
#include <regex>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
  ifstream input("input.txt");
  long sum = 0;

  string line;
  while (getline(input, line)) {
    line = regex_replace(line, regex(R"(one)"),   "o1e");
    line = regex_replace(line, regex(R"(two)"),   "t2o");
    line = regex_replace(line, regex(R"(three)"), "t3e");
    line = regex_replace(line, regex(R"(four)"),  "f4r");
    line = regex_replace(line, regex(R"(five)"),  "f5e");
    line = regex_replace(line, regex(R"(six)"),   "s6x");
    line = regex_replace(line, regex(R"(seven)"), "s7n");
    line = regex_replace(line, regex(R"(eight)"), "e8t");
    line = regex_replace(line, regex(R"(nine)"),  "n9e");

    string digits = regex_replace(line, regex(R"([\D])"), "");
    if (digits.length() == 1) {
      sum += stol(digits) * 11;
    } else if (digits.length() > 1) {
      digits.erase(1, digits.length()-2);
      sum += stol(digits);
    }
  }

  printf("%ld\n", sum);
}
