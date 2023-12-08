#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

std::regex rgx("([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)");
std::map<string, std::pair<string, string>> maps; 

void solve() {
  string directions;
  getline(cin, directions);

  string dump;
  getline(cin, dump);

  string mapping;
  while (getline(cin, mapping)) {
    smatch rgx_match;
    regex_search(mapping, rgx_match, rgx);

    maps[rgx_match[1]] = make_pair(rgx_match[2], rgx_match[3]);
  }

  long answer = 0;
  string loc = "AAA";
  for (auto dir_idx = 0; dir_idx < directions.size(); dir_idx = (dir_idx+1) % directions.size()) {
    answer++;
    switch (directions[dir_idx]) {
      case 'L':
        loc = maps[loc].first;
        break;
      case 'R':
        loc = maps[loc].second;
        break;
      default:
        break;
    }
    if (loc == "ZZZ") {
      break;
    }
  }
  std::cout << answer << std::endl;
}

int main(int argc, char* argv[]) {
  solve();
  return 0;    
}
