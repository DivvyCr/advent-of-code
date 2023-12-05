#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

ifstream input("input.txt");
string dump;

void process_map(std::vector<long>* nums) {
  getline(input, dump);

  // Necessary to avoid numbers being affected more than once:
  std::vector<long> new_nums = *nums;

  string data;
  while (getline(input, data) && !data.empty()) {
    istringstream iss(data);

    long src, dest, range;
    iss >> dest >> src >> range;
    /* std::cout << src << "-" << src+range-1 << " -> " << dest << "+" << dest-src << std::endl; */

    int idx = 0;
    for (auto &num : *nums) {
      if (num >= src && num < src+range) {
        new_nums[idx] += dest-src;
      }
      idx++;
    }
  }

  *nums = new_nums;
}

int main() {
  string seeds;
  getline(input, seeds);

  istringstream iss(seeds);
  iss >> dump;

  std::vector<long> seed_nums;
  long seed_num;
  while (iss >> seed_num) {
    seed_nums.push_back(seed_num);
  }
  
  getline(input, dump);
  for (int i = 0; i < 7; i++) {
    process_map(&seed_nums);
  }

  sort(seed_nums.begin(), seed_nums.end());
  for (auto &x : seed_nums) {
    std::cout << x << std::endl;
  }

  return 0;
}
