#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <utility>

using namespace std;

ifstream input("input.txt");
string dump;

struct DATA {
  DATA(long s, long r, bool c) : start(s), range(r), changed(c) {}
  long start;
  long range;
  bool changed;
};

void process_map(std::vector<DATA>* nums) {
  getline(input, dump);

  std::vector<DATA> queue;
  std::vector<DATA> buffer; 
  std::vector<DATA> done;

  for (auto &n : *nums) {
    n.changed = false;
    queue.push_back(n);
  }

  string map_entry;
  long src, dest, range;
  while (getline(input, map_entry) && !map_entry.empty()) {
    /* std::cout << std::endl; */
    /* std::cout << map_entry << std::endl; */
    istringstream entry_stream(map_entry);
    entry_stream >> dest >> src >> range;

    for (auto &data_range : queue) {
      if (data_range.changed) continue;

      long dr_start = data_range.start;
      long dr_end = data_range.start + data_range.range;

      long mapped_diff = dest - src;
      long mapped_end = src + range;

      /* std::cout << dr_start << "-" << dr_end << std::endl; */
      if (dr_start >= src && dr_end <= mapped_end) {
        // Data range is fully contained in mapped range
        data_range.changed = true;
        done.push_back(DATA(data_range.start + mapped_diff, data_range.range, true));
        /* std::cout << "Upd: " << data_range.start+mapped_diff << "-" << data_range.range << std::endl; */
      }
      else if (dr_start < src && dr_end > mapped_end) {
        // Data range fully contains mapped range
        data_range.changed = true;
        done.push_back(DATA(src + mapped_diff, range, true));
        /* std::cout << "Upd: " << src+mapped_diff << "-" << src+mapped_diff+range << std::endl; */
        buffer.push_back(DATA(dr_start, src - dr_start, false));
        /* std::cout << "New: " << dr_start << "-" << src-dr_start << std::endl; */
        buffer.push_back(DATA(src + range, dr_end - mapped_end, false));
        /* std::cout << "New: " << src+range << "-" << dr_end-mapped_end << std::endl; */
      }
      else if (dr_start < src && dr_end >= src && dr_end <= mapped_end) {
        // Data range begins before mapped range but ends inside it
        data_range.changed = true;
        done.push_back(DATA(src + mapped_diff, dr_end - src, true));
        /* std::cout << "Upd: " << src+mapped_diff << "-" << dr_end+mapped_diff << std::endl; */
        buffer.push_back(DATA(dr_start, src - dr_start, false));
        /* std::cout << "New: " << dr_start << "-" << src << std::endl; */
      }
      else if (dr_start >= src && dr_start < mapped_end && dr_end > mapped_end) {
        // Data range begins in mapped range but ends outside it:
        data_range.changed = true;
        done.push_back(DATA(dr_start + mapped_diff, mapped_end - dr_start, true));
        /* std::cout << "Upd: " << dr_start+mapped_diff << "-" << mapped_end+mapped_diff << std::endl; */
        buffer.push_back(DATA(mapped_end, dr_end - mapped_end, false));
        /* std::cout << "New: " << mapped_end << "-" << dr_end-mapped_end << std::endl; */
      }
    }
    for (auto &q : queue) if (!q.changed) buffer.push_back(q);
    queue = buffer;
    buffer.clear();
  }
  for (auto &q : queue) done.push_back(q);
  *nums = done;
}

int main() {
  string seed_line;
  getline(input, seed_line);

  istringstream seed_stream(seed_line);
  seed_stream >> dump;

  std::vector<DATA> seeds;
  long seed_num, seed_range;
  while (seed_stream >> seed_num >> seed_range) {
    seeds.push_back(DATA(seed_num, seed_range, false));
  }
  
  getline(input, dump);
  for (int i = 0; i < 7; i++) process_map(&seeds);

  long min_seed = LONG_MAX;
  for (auto &x : seeds) {
    if (x.start < min_seed) min_seed = x.start;
  }
  std::cout << min_seed << std::endl;

  return 0;
}
