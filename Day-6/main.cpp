#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void solve() {
  long long t = 44826981;
  long long d = 202107611381458;

  long long count = 0;
  for (long long i = 0; i < t; i++) {
    if (i*(t-i) > d) count++;
  }
  std::cout << count << std::endl;
}

int main(int argc, char* argv[]) {
  solve();
  return 0;    
}
