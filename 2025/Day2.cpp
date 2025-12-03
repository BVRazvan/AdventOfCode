#include <iostream>
#include <fstream>
#include <format>
#include <vector>
#include <utility>
#include <sstream>
#include <set>

constexpr long long UPPER_LIMIT = 1e12, BASE_LIMIT = 1e7;

std::vector<std::pair<long long, long long>> getIntervals(std::istringstream&& is) {
    std::string interval;
    std::vector<std::pair<long long, long long>> intervals;
    while (getline(is, interval, ',')) {
        int pos = interval.find('-');
        intervals.emplace_back(std::make_pair(stoll(interval.substr(0, pos)), stoll(interval.substr(pos + 1, interval.length() - pos))));
    }
    return intervals;
}

void addDuplicate(long long& val, long long base) {
    long long p10 = 1;
    while (base / p10 > 0) {
        p10 *= 10;
    }
    val *= p10;
    val += base;
}

void calculateMatches(long long start, std::vector<std::set<long long>>& vSet, std::vector<std::pair<long long, long long>>& intervals, long long& sol) {
    long long value = start;
    do {
        addDuplicate(value, start);
        for (int i = 0; i < int(intervals.size()); ++i) {
            const auto& [x, y] = intervals[i];
            if (value >= x && value <= y) {
                if (vSet[i].contains(value)) {
                    continue;
                }
                vSet[i].insert(value);
                sol += value;
                break;
            }
        }
    } while (value < UPPER_LIMIT);
}

void solve(std::ifstream& in) {
    std::string str;
    getline(in, str);
    auto intervals = getIntervals(std::istringstream(str));
    long long sol = 0;
    std::vector<std::set<long long>> vSet(intervals.size());
    for (long long val = 1; val <= BASE_LIMIT; ++val) {
        calculateMatches(val, vSet, intervals, sol);
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
    solve(in);
    return 0;
}
