std::vector<int> v1, v2;
std::map<int, int> cnt;

void readInput() {
    int x, y;
    v1.clear();
    v2.clear();
    while (cin >> x >> y) {
        v1.push_back(x);
        v2.push_back(y);
    }
}

void solvePartOne() {
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    long long sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += abs(v1[i] - v2[i]);
    }
    cout << "Ans = " << sum << endl;
}

void solvePartTwo() {
    cnt.clear();
    for (auto v : v2)
        cnt[v]++;
    long long sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += 1ll * v1[i] * cnt[v1[i]];
    }
    cout << "Ans = " << sum << endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}