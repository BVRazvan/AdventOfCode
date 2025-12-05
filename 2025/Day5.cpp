#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <algorithm>

void solve(std::ifstream& in) {
	std::string line {};
	bool emptyLine {};
	std::vector<long long> q;
	std::vector<std::pair<long long, long long>> intervals;
	while (getline(in, line)) {
		if (emptyLine) {
			q.emplace_back(std::stoll(line));
			continue;
		}
		if (!int(line.length())) {
			emptyLine = true;
			continue;
		}
		int pos = line.find('-');
		intervals.emplace_back(std::make_pair(std::stoll(line.substr(0, pos)), std::stoll(line.substr(pos + 1))));
	}
	std::sort(q.begin(), q.end());
	std::sort(intervals.begin(), intervals.end());
	long long sol {};
	long long r {-1};
	for (const auto& [x, y] : intervals) {
		if (x > r) {
			sol += (y - x + 1);
			r = y;
			continue;
		}
		if (y > r) {
			sol += (y - r);
			r = y;
			continue;
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