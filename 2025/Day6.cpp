#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void solve(std::ifstream& in) {
	std::string line;
	std::vector<std::string> lines;
	while (getline(in, line)) {
		lines.emplace_back(line);
	}
	int nofLines = int(lines.size());
	int lineLen = int(lines[0].size());
	// long long sol {};
	std::vector<std::vector<long long>> numberGroups;
	std::vector<long long> numbers;
	for (int j = lineLen - 1; j >= 0; --j) {
		long long cnt {};
		for (int i = 0; i < nofLines - 1; ++i) {
			if (lines[i][j] >= '0' && lines[i][j] <= '9') {
				cnt = cnt * 10 + (lines[i][j] - '0');
			}
		}
		if (cnt > 0) {
			numbers.emplace_back(cnt);
		} else if (int(numbers.size())) {
			numberGroups.emplace_back(numbers);
			numbers.clear();
		}
	}
	if (int(numbers.size())) {
		numberGroups.emplace_back(numbers);
	}
	std::vector<char> signs;
	for (int j = lineLen - 1; j >= 0; --j) {
		if (lines[nofLines - 1][j] != ' ') {
			signs.emplace_back(lines[nofLines - 1][j]);
		}
	}
	long long sol {};
	int nofGroups = int(numberGroups.size());
	for (int i = 0; i < nofGroups; ++i) {
		long long cnt = (signs[i] == '*' ? 1 : 0);
		for (const auto number : numberGroups[i]) {
			if (signs[i] == '*') {
				cnt *= number;
			} else {
				cnt += number;
			}
		}
		sol += cnt;
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