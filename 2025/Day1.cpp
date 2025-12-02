#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <string_view>

void solve(std::ifstream& in, const int startPos, const int maxPos, int type = 1) {
  int position = startPos;
  int sol = 0;
  std::string line;
  while (1) {
    char direction = in.get();
    if (direction == EOF) {
      break;
    }
    getline(in, line);
    int delta = stoi(line);
    if (direction == 'L') {
      delta *= (-1);
    }
    if (type == 1) {
      position += delta;
      if (position % maxPos == 0) {
        sol += 1;
      }
      continue;
    } 
    if (delta < 0) {
      if (abs(delta) < position) {
        position += delta;
        continue;
      }
      if (position != 0) {
        delta += position;
        position = 0;
        sol += 1;
      }
      sol += abs(delta) / maxPos;
      position = maxPos - abs(delta) % maxPos;
      if (position == maxPos) {
        position = 0;
      }
    } else {
      if (delta < maxPos - position) {
        position += delta;
        continue;
      }
      delta -= (maxPos - position);
      position = 0;
      sol += 1;
      position += delta;
      position %= maxPos;
      sol += delta / maxPos;
    }
  }
  std::cout << sol << '\n';
  return;
}

int main() {
  std::string filename("input");
  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cout << format("Failed to open {}!\n", filename);
    return -1;
  }
  solve(in, 50, 100, 2);
  return 0;
}