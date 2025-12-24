std::vector<long long> stone;

void readInput() {
    int val;
    while (cin >> val) {
        stone.push_back(1ll * val);
    }
}

long long llPow10(int n) {
    long long r = 1; while (n--) r *= 10; return r;
}

bool splitEven(long long val, long long& lhs, long long& rhs) {
    for (int nDigit = 1; ; nDigit++) {
        if (llPow10(nDigit - 1) <= val && val <= llPow10(nDigit) - 1) {
            if (nDigit % 2 != 0) return false;
            int halfDig = nDigit / 2;
            lhs = val / llPow10(halfDig);
            rhs = val % llPow10(halfDig);
            return true;
        }
    }
    return false;
}

void solvePartOne() {
    for (int times = 0; times < 25; times++) {
        std::vector<long long> newStone = {};
        for (int i = 0; i < stone.size(); i++) {
            long long lhs, rhs;
            if (stone[i] == 0) {
                newStone.push_back(1);
            } else if (splitEven(stone[i], lhs, rhs)) {
                newStone.push_back(lhs); newStone.push_back(rhs);
            } else {
                newStone.push_back(stone[i] * 2024);
            }
        }
        stone = newStone;
        // for (auto v : stone) std::cout << v << " "; std::cout << std::endl;
    }
    long long answer = 0;
    answer = stone.size();
    std::cout << "Answer = " << answer << std::endl;
}

std::vector<std::pair<long long, long long>> S, newS;

void merge() {
    std::sort(S.begin(), S.end());
    std::vector<std::pair<long long, long long>> newS = {};
    int isFirst = 1;
    long long accCount = 0;
    for (int i = 0; i < S.size(); i++) {
        if (i == 0 || S[i].first != S[i - 1].first) {
            if (!isFirst) {
                newS.push_back({S[i - 1].first, accCount});
            }
            accCount = S[i].second;
            isFirst = 0;
        } else {
            accCount += S[i].second;
        }
    }
    if (!isFirst) {
        newS.push_back({S[S.size() - 1].first, accCount});
    }
    S = newS;
}

void solvePartTwo() {
    S.clear();
    for (auto v : stone) S.push_back({v, 1});
    merge();
    for (int times = 0; times < 75; times++) {
        newS.clear();
        for (int i = 0; i < S.size(); i++) {
            long long lhs, rhs;
            auto [val, cnt] = S[i];
            if (val == 0) {
                newS.push_back({1, cnt});
            } else if (splitEven(val, lhs, rhs)) {
                newS.push_back({lhs, cnt}); newS.push_back({rhs, cnt});
            } else {
                newS.push_back({val * 2024, cnt});
            }
        }
        S = newS;
        merge();
        // for (auto [x, y] : S) std::cout << x << " "; std::cout << std::endl;
    }
    long long answer = 0;
    for (auto [x, y] : S) answer += y;
    std::cout << "Answer = " << answer << std::endl;
}

int main() {
    readInput();
    // std::cout << "Solving Part One:" << std::endl;
    // solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}