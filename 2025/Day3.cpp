#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
constexpr int NOF_DIGITS = 12;

long long solve(std::ifstream& is) {
  std::string line;
  long long sol = 0;
  while (getline(is, line)) {
    std::array<int, NOF_DIGITS> mx{};
    int len = int(line.length());
    int digit = 0;
    for (int i = 0; i < len; ++i) {
      digit = line[i] - '0';
      for (int j = std::max(NOF_DIGITS - len + i, 0); j < NOF_DIGITS; ++j) {
        if (digit > mx[j]) {
            mx[j] = digit;
            std::fill(mx.begin() + j + 1, mx.end(), 0); 
            break;
        }
      }
    }
    long long p10 = 1;
    std::reverse(mx.begin(), mx.end());
    for (auto val : mx) {
      sol += 1LL * val * p10;
      p10 *= 10;
    }
  }
  return sol;
}

int main() {
  std::string filename("input");
  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cout << format("Failed to open {}!\n", filename);
    return -1;
  }
  std::cout << solve(in);
  return 0;
}