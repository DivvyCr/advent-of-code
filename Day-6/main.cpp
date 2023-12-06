#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// g++ -std=c++17 -g -Wall main.cpp -o out 
// ./out < input

void solve() {
  string times;
  string distances;
  getline(cin, times);
  getline(cin, distances);
  
  string dump;
  istringstream itime(times);
  istringstream idist(distances);
  itime >> dump;
  idist >> dump;

  long long answer = 1;
  long t, d, result;
  for (long i = 0; i < 4; i++) {
    itime >> t;
    idist >> d;
    long count = 0;
    for (long j = 1; j < t; j++) {
      result = j*(t-j);
      if (result > d) count++;
    }
    std::cout << count << std::endl;
    answer *= count;
  }
  std::cout << answer << std::endl;
}

int main(int argc, char* argv[]) {
  solve();

  return 0;    
}
