#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

std::regex rgx("([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)");
std::map<string, std::pair<string, string>> maps; 

void solve() {
  string directions;
  getline(cin, directions);

  string dump;
  getline(cin, dump);

  string mapping;
  std::vector<string> locs;
  while (getline(cin, mapping)) {
    smatch rgx_match;
    regex_search(mapping, rgx_match, rgx);

    maps[rgx_match[1]] = make_pair(rgx_match[2], rgx_match[3]);
    if (rgx_match[1].str()[2] == 'A') locs.push_back(rgx_match[1]);
  }

  long steps = 0;
  std::map<int, long> found;
  for (auto dir_idx = 0; dir_idx < directions.size(); dir_idx = (dir_idx+1) % directions.size()) {
    steps++;
    for (int i = 0; i < locs.size(); i++) {
      switch (directions[dir_idx]) {
        case 'L':
          locs[i] = maps[locs[i]].first;
          break;
        case 'R':
          locs[i] = maps[locs[i]].second;
          break;
        default:
          break;
      }
      if (locs[i][2] == 'Z') found[i] = steps;
    }
    if (found.size() == locs.size()) break;
  }

  long answer = 1; // NOTE: I 'cheated' by looking at discussions; unique cycles are not obvious here.
  for (auto &f : found) answer = std::lcm(answer, f.second);
  std::cout << answer << std::endl;
}

int main(int argc, char* argv[]) {
  solve();
  return 0;    
}
