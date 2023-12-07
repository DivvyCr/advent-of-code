#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void temp(int rank, std::pair<string, int> hand);
bool handBetterThan(string h1, string h2);

std::map<int, std::vector<std::pair<string, int>>> sorted_hands; 

void solve() {
  long num_hands = 0;

  string hand, bid_str;
  std::map<char, int> hand_cards;

  while (cin >> hand >> bid_str) {
    num_hands++;
    hand_cards.clear();

    int bid = stoi(bid_str);
    for (auto &card : hand) hand_cards[card]++;

    switch (hand_cards.size()) {
      case 1: // five-of-a-kind
        temp(0, make_pair(hand, bid));
        break;
      case 2: // four-of-a-kind OR full house
        {
          bool is_full_house = false;
          for (auto &c : hand_cards) {
            if (c.second == 2 || c.second == 3) {
              is_full_house = true;
              break;
            }
          }
          if (is_full_house) {
            temp(2, make_pair(hand, bid));
          } else {
            temp(1, make_pair(hand, bid));
          }
        }
        break;
      case 3: // three-of-a-kind OR two pair
        {
          bool is_two_pair = false;
          for (auto &c : hand_cards) {
            if (c.second == 2) {
              is_two_pair = true;
              break;
            }
          }
          if (is_two_pair) {
            temp(4, make_pair(hand, bid));
          } else {
            temp(3, make_pair(hand, bid));
          }
        }
        break;
      case 4: // pair
        temp(5, make_pair(hand, bid));
        break;
      case 5: // high card
        temp(6, make_pair(hand, bid));
        break;
      default: // unreachable
        break;
    }
  }

  long long answer = 0;
  long cur_rank = num_hands;
  for (auto &ranked_hands : sorted_hands) {
    for (auto &hand : ranked_hands.second) {
      /* std::cout << cur_rank << ". " << hand.first << std::endl; */
      answer += cur_rank * hand.second;
      cur_rank--;
    }
  }
  std::cout << answer << std::endl;
}

void temp(int rank, pair<string, int> hand) {
  if (sorted_hands[rank].empty()) {
    sorted_hands[rank].push_back(hand);
  } else {
    for (auto idx = 0; idx < sorted_hands[rank].size(); idx++) {
      auto h = sorted_hands[rank][idx];
      if (handBetterThan(h.first, hand.first)) {
        continue;
      } else {
        sorted_hands[rank].insert(sorted_hands[rank].begin()+idx, hand);
        return;
      }
    }
    sorted_hands[rank].push_back(hand);
  }
}

bool handBetterThan(string h1, string h2) {
  for (int i = 0; i < 5; i++) {
    if (h1[i] == h2[i]) continue;
    if (h1[i] == 'A') return true;
    if (h2[i] == 'A') return false;
    if (h1[i] == 'K') return true;
    if (h2[i] == 'K') return false;
    if (h1[i] == 'Q') return true;
    if (h2[i] == 'Q') return false;
    if (h1[i] == 'J') return true;
    if (h2[i] == 'J') return false;
    return h1 > h2;
  }
}

int main(int argc, char* argv[]) {
  solve();
  return 0;
}
