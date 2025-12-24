std::vector<std::vector<int>> page;
std::vector<std::pair<int, int>> ordering;

void readInput() {
    ordering.clear();
    page.clear();
    string line;
    int isReadingOrder = 1;
    while (getline(cin, line)) {
        if (line.empty()) {isReadingOrder = 0; continue;}
        if (isReadingOrder) {
            string replaceLine = "";
            for (int i = 0; i < line.size(); i++) if (line[i] != '|') replaceLine.push_back(line[i]); else replaceLine.push_back(' ');
            stringstream sin(replaceLine);
            int x, y;
            sin >> x >> y;
            ordering.push_back({x, y});
        } else {
            string replaceLine = "";
            for (int i = 0; i < line.size(); i++) if (line[i] != ',') replaceLine.push_back(line[i]); else replaceLine.push_back(' ');
            stringstream sin(replaceLine);
            std::vector<int> curPage; curPage.clear();
            int val;
            while (sin >> val) curPage.push_back(val);
            page.push_back(curPage);
        }
    }
}

void solvePartOne() {
    long long sum = 0;
    for (auto curPage : page) {
        int n = curPage.size();
        int midNum = curPage[n / 2];
        std::map<int, int> pos;
        pos.clear();
        for (int i = 0; i < n; i++) {
            pos[curPage[i]] = i;
            // std::cout << curPage[i] << " " << i << std::endl;
        }
        int isOK = 1;
        for (auto [x, y] : ordering) {
            // std::cout << x << " | " << y << std::endl;
            if (pos.count(x) > 0 && pos.count(y) > 0) {
                // std::cout << x << " " << y << " " << pos[x] << " " << pos[y] << std::endl;
                isOK &= pos[x] < pos[y];
            }
        }
        // std::cout << "ok?: " << isOK << std::endl;
        if (isOK) sum += midNum;
    }
    std::cout << "Ans = " << sum << std::endl;
}

void solvePartTwo() {
    long long sum = 0;
    for (auto curPage : page) {
        int n = curPage.size();
        std::map<int, int> pos;
        pos.clear();
        for (int i = 0; i < n; i++) {
            pos[curPage[i]] = i;
            // std::cout << curPage[i] << " " << i << std::endl;
        }
        int isOK = 1;
        int posA, posB;
        for (auto [x, y] : ordering) {
            // std::cout << x << " | " << y << std::endl;
            if (pos.count(x) > 0 && pos.count(y) > 0) {
                // std::cout << x << " " << y << " " << pos[x] << " " << pos[y] << std::endl;
                if (pos[x] >= pos[y]) {
                    // assert(isOK);
                    posA = pos[x]; posB = pos[y];
                }
                isOK &= pos[x] < pos[y];
            }
        }
        // std::cout << "ok?: " << isOK << std::endl;
        if (!isOK) {
            auto cmp = [&](const int &a, const int &b) {
                for (auto [x, y] : ordering) {
                    if (x == a && y == b) return true;
                    else if (x == b && y == a) return false;
                }
                return a < b;
            };
            std::sort(curPage.begin(), curPage.end(), cmp);
            int midNum = curPage[n / 2];
            sum += midNum;
        }
    }
    std::cout << "Ans = " << sum << std::endl;
}

int main() {
    readInput();
    std::cout << "Solving Part One:" << std::endl;
    solvePartOne();
    std::cout << "Solving Part Two:" << std::endl;
    solvePartTwo();
}