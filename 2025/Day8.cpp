#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <array>
#include <format>
#include <queue>
#include <numeric>

long long findDistance(const std::tuple<long long, int, int>& a, const std::tuple<long long, int, int>& b) {
  long long sol {};
  sol += 1LL * (std::get<0>(a) - std::get<0>(b)) * (std::get<0>(a) - std::get<0>(b)) +
         1LL * (std::get<1>(a) - std::get<1>(b)) * (std::get<1>(a) - std::get<1>(b)) +
         1LL * (std::get<2>(a) - std::get<2>(b)) * (std::get<2>(a) - std::get<2>(b));
  return sol;
}

void makeSet(std::vector<int>& Size, std::vector<int>& parent, int idx) {
  Size[idx] = 1;
  parent[idx] = idx;
}

int findSet(std::vector<int>& parent, int idx) {
  if (parent[idx] == idx) {
    return idx;
  }
  return parent[idx] = findSet(parent, parent[idx]);
}

bool uniteSets(std::vector<int>& Size, std::vector<int>& parent, int x, int y, int n) {
  x = findSet(parent, x);
  y = findSet(parent, y);
  if (x == y) { 
    return false;
  }
  if (Size[y] > Size[x]) {
    std::swap(x, y);
  }
  parent[y] = x;
  Size[x] += Size[y];
  if (Size[x] == n) {
    return true;
  }
  return false;
}

void solve(std::ifstream& in) {
  std::string line;
  std::vector<std::tuple<int, int, int>> pts;
  while (getline(in, line)) {
    std::istringstream is(line);
    std::string word;
    std::array<int, 3> vals; 
    for (int i = 0; getline(is, word, ','); ++i) {
      vals[i] = std::stoi(word);
    }
    pts.emplace_back(vals);
  }
  int n = int(pts.size());
  std::vector<std::tuple<long long, int, int>> edges;
  for (int i {}; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      edges.emplace_back(std::make_tuple(findDistance(pts[i], pts[j]), i, j));
    }
  }
  std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
    return std::get<0>(a) < std::get<0>(b);
  });
  std::vector<int> Size(n), parent(n);
  for (int i = 0; i < n; ++i) {
    makeSet(Size, parent, i);
  }
  for (const auto& [dist, x, y] : edges) {
    if (uniteSets(Size, parent, x, y, n)) {
      std::cout << 1LL * std::get<0>(pts[x]) * std::get<0>(pts[y]) << '\n';
      return;
    }
  }
  return;
}

int main() {
	std::string filename {"input"};
	std::ifstream in {filename};
	if (!in.is_open()) {
    std::cout << std::format("Failed to open {}!\n", filename);
    return -1;
	}
	solve(in);
	return 0;
}
