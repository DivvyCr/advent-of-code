#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void solve() {
  string line;
  while (getline(cin, line)) {
    istringstream iss(line);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " < INPUT" << endl;
    exit(1);
  }

  solve();

  return 0;    
}
