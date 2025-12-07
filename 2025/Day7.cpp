#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>

std::pair<int, int> findStart(std::vector<std::string>& lines) {
  int n = int(lines.size());
  int m = int(lines[0].length());
  for (int i {}; i < n; ++i) {
    for (int j {}; j < m; ++j) {
      if (lines[i][j] == 'S') {
        return std::make_pair(i, j);
      }
    }
  }
  return std::make_pair(-1, -1);
}

void solve(std::ifstream& in) {
  std::vector<std::string> lines;
  std::string line;
  while (getline(in, line)) {
    lines.emplace_back(line);
  }
  int n = int(lines.size());
  int m = int(lines[0].length());
  auto start = findStart(lines);
  auto inside = [&](int x, int y) -> bool {
    return x >= 0 && x < n && y >= 0 && y < m;
  };
  std::vector<std::pair<int, int>> dir {{1, -1}, {1, 1}};
  std::queue<std::pair<int, int>> q;
  std::set<std::pair<int, int>> seen;
  std::vector<std::vector<long long>> dp(n, std::vector<long long>(m, 0));
  long long sol {};
  dp[start.first][start.second] = 1;
  q.push(start);
  while (!q.empty()) {
    const auto [x, y] = q.front();
    q.pop();
    if (!inside(x, y)) {
      continue;
    }
    if (seen.find(std::make_pair(x, y)) != seen.end()) {
      continue;
    }
    seen.insert(std::make_pair(x, y));
    if (x + 1 == n) {
      sol += dp[x][y];
    } else if (lines[x + 1][y] == '^') {
      for (const auto& [dx, dy] : dir) {
        int l = x + dx;
        int c = y + dy;
        if (!inside(l, c)) {
          continue;
        }
        dp[l][c] += dp[x][y];
        q.push(std::make_pair(l, c));
      }
    } else {
      dp[x + 1][y] += dp[x][y];
      q.push(std::make_pair(x + 1, y));
    }
  }
  std::cout << sol << '\n';
  return;
}

int main() {
	std::string filename {"input"};
	std::ifstream in {filename};
	if (!in.is_open()) {
    std::cout << format("Failed to open {}!\n", filename);
    return -1;
	}
	solve(in);
	return 0;
}
