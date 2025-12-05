#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

void solve(std::ifstream& in) {
  std::string line;
  std::vector<std::string> lines;
  while (getline(in, line)) {
    lines.emplace_back(line);
  }
  std::array<std::pair<int, int>, 8> dir {std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(0, -1),
                                            std::make_pair(-1, 1), std::make_pair(1, 1), std::make_pair(1, -1), std::make_pair(-1, -1)};
  int n {int(lines.size())};
  int m {int(lines[0].size())};
  auto inside = [&](int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
  };
  int sol {};
  std::queue<std::pair<int, int>> q;
  for (int i {}; i < n; ++i) {
    for (int j {}; j < m; ++j) {
      q.emplace(std::make_pair(i, j));
    }
  }
  while (!q.empty()) {
    const auto [x, y] = q.front();
    q.pop();
    if (lines[x][y] != '@') {
      continue;
    }
    int cnt {};
    for (const auto& [dx, dy] : dir) {
      int l {x + dx};
      int c {y + dy};
      if (!inside(l, c)) {
        continue;
      }
      cnt += lines[l][c] == '@';
    }
    if (cnt >= 4) {
      continue;
    }
    sol += 1;
    lines[x][y] = '.';
    for (const auto& [dx, dy] : dir) {
      int l {x + dx};
      int c {y + dy};
      if (!inside(l, c) || lines[l][c] != '@') {
        continue;
      }
      q.emplace(std::make_pair(l, c));
    } 
  }
  std::cout << sol << '\n';
  return;
}

int main() {
  std::string filename {"input"};
  std::ifstream in {filename};
  solve(in);
  return 0;
}